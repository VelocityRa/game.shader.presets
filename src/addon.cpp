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
#include "utils/CommonIncludes.h"
#include "utils/CommonMacros.h"
#include "utils/URIUtils.h"

#include <algorithm>
#include <fstream>
#include <memory>
#include <streams/file_stream.h>
#include <vector>

using namespace SHADER;


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

// CInstanceShaderPreset overrides

// ======== CONFIG_FILE ========

config_file_t_* CShaderPreset::ConfigFileNew(const char* path, const char* basePath)
{
  m_basePath = basePath;
  return reinterpret_cast<config_file_t_*>(config_file_new(path));
}

config_file_t_* CShaderPreset::ConfigFileNewFromString(const char* from_string)
{
  return reinterpret_cast<config_file_t_*>(config_file_new_from_string(from_string));
}

void CShaderPreset::ConfigFileFree(config_file_t_* conf)
{
  config_file_free(reinterpret_cast<config_file_t*>(conf));
}

// =============================

// ==== VIDEO_SHADER_PARSE =====

bool CShaderPreset::ShaderPresetRead(config_file_t_* conf, video_shader_* shader)
{
  {
    bool readResult = video_shader_read_conf_cgp(
      reinterpret_cast<config_file_t*>(conf),
      reinterpret_cast<video_shader*>(shader));
    if (!readResult)
      return false;
  }
  if (!m_basePath.empty())
  {
    for (unsigned passIdx = 0; passIdx < shader->passes; ++passIdx)
    {
      auto& pass = shader->pass[passIdx];
      char* shaderSource = nullptr;
      std::string relativePresetPath = pass.source.path;
      std::string absolutePresetPath = m_basePath + relativePresetPath;

      // Fix windows paths
      std::replace(absolutePresetPath.begin(), absolutePresetPath.end(), '\\', '/');
      // Resolve relative paths ("../")
      absolutePresetPath = URIUtils::CanonicalizePath(absolutePresetPath, '/');
      int readResult = filestream_read_file(absolutePresetPath.c_str(),
        reinterpret_cast<void**>(&shaderSource), nullptr);
      if (readResult == -1)
        return false;

      // Assign same source to both fields, just make sure we don't double free on Kodi's side
      pass.source.string.fragment = shaderSource;
      pass.source.string.vertex = shaderSource;
    }
  }
  return true;
}

void CShaderPreset::ShaderPresetWrite(config_file_t_* conf, struct video_shader_* shader)
{
  video_shader_write_conf_cgp(
    reinterpret_cast<config_file_t*>(conf),
    reinterpret_cast<video_shader*>(shader));
}

void CShaderPreset::ShaderPresetResolveRelative(struct video_shader_* shader, const char* ref_path)
{
  video_shader_resolve_relative(
    reinterpret_cast<video_shader*>(shader),
    ref_path);
}

bool CShaderPreset::ShaderPresetResolveCurrentParameters(config_file_t_* conf, struct video_shader_* shader)
{
  return video_shader_resolve_current_parameters(
    reinterpret_cast<config_file_t*>(conf),
    reinterpret_cast<video_shader*>(shader));
}

bool CShaderPreset::ShaderPresetResolveParameters(config_file_t_* conf, struct video_shader_* shader)
{
  return video_shader_resolve_parameters(
    reinterpret_cast<config_file_t*>(conf),
    reinterpret_cast<video_shader*>(shader));
}

ADDONCREATOR(CShaderPreset) // Don't touch this!
