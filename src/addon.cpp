/*
 *      Copyright (C) 2017 Nick Renieris
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

#include <file/config_file.h>
#include "gfx/video_shader_parse.h"
#include "filesystem/Filesystem.h"
#include "log/Log.h"
#include "log/LogAddon.h"
#include "utils/CommonIncludes.h"
#include "utils/CommonMacros.h"

#include <algorithm>
#include <vector>

using namespace SHADER;

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

CShaderPreset::~CShaderPreset()
{
  CFilesystem::Deinitialize();

  CLog::Get().SetType(SYS_LOG_TYPE_CONSOLE);
}


int CShaderPreset::GetTest(unsigned int test_arg)
{
  CLog::Get().SetType(SYS_LOG_TYPE_ADDON);
  CLog::Get().Log(SYS_LOG_INFO, "TESTING BINARY ADDON %d", test_arg);
  CLog::Get().SetType(SYS_LOG_TYPE_CONSOLE);
  CLog::Get().Log(SYS_LOG_INFO, "TESTING BINARY ADDON SECOND");

  return test_arg + 5;
}

/// ======== CONFIG_FILE ========

config_file_t* wrapper_config_file_new(const char *path)
{
  config_file_new(path);
}
config_file_t* wrapper_config_file_new_from_string(const char *from_string)
{
  config_file_new_from_string(from_string);
}
void wrapper_config_file_free(config_file_t *conf)
{
  config_file_free(conf);
}

/// =============================
/// ==== VIDEO_SHADER_PARSE =====

bool CShaderPreset::wrapper_read_conf_path_cgp(const char *conf_path, struct video_shader *shader)
{
  config_file_t *conf = config_file_new(conf_path);
  video_shader *shader = calloc(1, sizeof(video_shader)); // TODO: Use new maybe

  CLog::Get().Log(SYS_LOG_INFO, "PASSES: %d", shader->passes);
  CLog::Get().Log(SYS_LOG_INFO, "VARS: %d", shader->variables);

  bool returnStatus = video_shader_read_conf_cgp(conf, shader);
  // TODO: config_file_free
  // config_file_free(conf)
  return returnStatus;
}
bool CShaderPreset::wrapper_read_conf_cgp(config_file_t *conf, struct video_shader *shader)
{
  return video_shader_read_conf_cgp(conf, shader);
}
void CShaderPreset::wrapper_write_conf_cgp(config_file_t *conf, struct video_shader *shader)
{
  video_shader_write_conf_cgp(conf, shader);
}
void CShaderPreset::wrapper_resolve_relative(struct video_shader *shader, const char *ref_path)
{
  video_shader_resolve_relative(shader, ref_path);
}
bool CShaderPreset::wrapper_resolve_current_parameters(config_file_t *conf, struct video_shader *shader)
{
  return video_shader_resolve_current_parameters(conf, shader);
}
bool CShaderPreset::wrapper_resolve_parameters(config_file_t *conf, struct video_shader *shader)
{
  return video_shader_resolve_parameters(conf, shader);
}
rarch_shader_type CShaderPreset::wrapper_parse_type(const char *path, rarch_shader_type fallback)
{
  return video_shader_wrapper_parse_type(path, fallback);
}

/// =============================

ADDONCREATOR(CShaderPreset) // Don't touch this!
