/*
 *      Copyright (C) 2017      Nick Renieris
 *      Copyright (C) 2014-2017 Garrett Brown
 *      Copyright (C) 2014-2017 Team Kodi
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "addon.h"

#include "file/config_file.h"
#include "filesystem/Filesystem.h"
#include "gfx/video_shader_parse.h"
#include "log/Log.h"
#include "log/LogAddon.h"
#include "utils/RarchTranslator.h"

#include <streams/file_stream.h>

using namespace SHADER;

struct shader_preset_file
{
  shader_preset_file(config_file_t *rarch_conf, const std::string &path) :
    rarch_conf(rarch_conf),
    path(path)
  {
  }

  config_file_t *rarch_conf = nullptr;
  std::string path;
};

CShaderPreset::~CShaderPreset()
{
  CFilesystem::Deinitialize();

  CLog::Get().SetType(SYS_LOG_TYPE_CONSOLE);
}

// CAddonBase overrides

ADDON_STATUS CShaderPreset::Create()
{
  CLog::Get().SetPipe(new CLogAddon());

  if (!CFilesystem::Initialize())
    return ADDON_STATUS_PERMANENT_FAILURE;

  return GetStatus();
}

ADDON_STATUS CShaderPreset::SetSetting(const std::string& settingName, const kodi::CSettingValue& settingValue)
{
  return ADDON_STATUS_OK;
}

ADDON_STATUS CShaderPreset::GetStatus()
{
  return ADDON_STATUS_OK;
}

preset_file CShaderPreset::PresetFileNew(const char *path)
{
  config_file_t *rarch_conf = config_file_new(path);

  if (rarch_conf != nullptr)
    return static_cast<preset_file>(new shader_preset_file(rarch_conf, path));

  return nullptr;
}

void CShaderPreset::PresetFileFree(preset_file file)
{
  shader_preset_file *preset_file = static_cast<shader_preset_file*>(file);

  config_file_free(preset_file->rarch_conf);

  delete preset_file;
}

bool CShaderPreset::ShaderPresetRead(preset_file file, video_shader &shader)
{
  shader_preset_file *preset_file = static_cast<shader_preset_file*>(file);

  rarch_video_shader rarch_shader;

  bool readResult = video_shader_read_conf_cgp(preset_file->rarch_conf, &rarch_shader);
  if (!readResult)
    return false;

  CRarchTranslator::TranslateShader(rarch_shader, shader, preset_file->path);

  for (unsigned passIdx = 0; passIdx < shader.pass_count; ++passIdx)
  {
    auto& pass = shader.passes[passIdx];
    pass.vertex_source = nullptr;
    pass.fragment_source = nullptr;

    // Read shader sources
    int readResult = filestream_read_file(pass.source_path, reinterpret_cast<void**>(&pass.vertex_source), nullptr);
    if (readResult == -1)
    {
      ShaderPresetFree(shader);
      return false;
    }
  }

  return true;
}

void CShaderPreset::ShaderPresetWrite(preset_file file, const video_shader &shader)
{
  shader_preset_file *preset_file = static_cast<shader_preset_file*>(file);

  rarch_video_shader rarch_shader;

  CRarchTranslator::TranslateShader(shader, rarch_shader, preset_file->path);

  video_shader_write_conf_cgp(preset_file->rarch_conf, &rarch_shader);

  CRarchTranslator::FreeShader(rarch_shader);
}

bool CShaderPreset::ShaderPresetResolveParameters(preset_file file, video_shader &shader)
{
  shader_preset_file *preset_file = static_cast<shader_preset_file*>(file);

  rarch_video_shader rarch_shader;

  CRarchTranslator::TranslateShader(shader, rarch_shader, preset_file->path);

  bool bSuccess = video_shader_resolve_parameters(preset_file->rarch_conf, &rarch_shader);

  if (bSuccess)
  {
    ShaderPresetFree(shader);
    CRarchTranslator::TranslateShader(rarch_shader, shader, preset_file->path);
  }

  CRarchTranslator::FreeShader(rarch_shader);

  return bSuccess;
}

void CShaderPreset::ShaderPresetFree(video_shader &shader)
{
  for (unsigned int i = 0; i < shader.pass_count; i++)
  {
    auto &pass = shader.passes[i];
    delete[] pass.source_path;
    delete[] pass.vertex_source;
    delete[] pass.fragment_source;
  }
  delete[] shader.passes;

  for (unsigned int i = 0; i < shader.lut_count; i++)
  {
    auto &lut = shader.luts[i];
    delete[] lut.id;
    delete[] lut.path;
  }
  delete[] shader.luts;

  for (unsigned int i = 0; i < shader.parameter_count; i++)
  {
    auto &parameter = shader.parameters[i];
    delete[] parameter.id;
    delete[] parameter.desc;
  }
  delete[] shader.parameters;
}

ADDONCREATOR(CShaderPreset) // Don't touch this!
