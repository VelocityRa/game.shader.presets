/*
 *      Copyright (C) 2017 Team Kodi
 *      http://kodi.tv
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
#pragma once

#include "gfx/video_shader_parse.h"

#include <kodi/addon-instance/ShaderPreset.h>

#include <string>

class CRarchTranslator
{
public:
  static SHADER_SCALE_TYPE TranslateScaleType(enum gfx_scale_type type);
  static enum gfx_scale_type TranslateScaleType(SHADER_SCALE_TYPE type);

  static SHADER_FILTER_TYPE TranslateFilterType(unsigned int type);
  static unsigned int TranslateFilterType(SHADER_FILTER_TYPE type);

  static SHADER_WRAP_TYPE TranslateWrapType(enum gfx_wrap_type type);
  static enum gfx_wrap_type TranslateWrapType(SHADER_WRAP_TYPE type);

  static void TranslateShaderPass(const rarch_video_shader_pass &rarch_pass, video_shader_pass &pass, const std::string &configPath);
  static void TranslateShaderPass(const video_shader_pass &pass, rarch_video_shader_pass &rarch_pass, const std::string &configPath);

  static void TranslateShaderLut(const rarch_video_shader_lut &rarch_lut, video_shader_lut &lut, const std::string &configPath);
  static void TranslateShaderLut(const video_shader_lut &lut, rarch_video_shader_lut &rarch_lut, const std::string &configPath);

  static void TranslateShaderParameter(const rarch_video_shader_parameter &rarch_param, video_shader_parameter &param);
  static void TranslateShaderParameter(const video_shader_parameter &param, rarch_video_shader_parameter &rarch_param);

  static void TranslateShader(const rarch_video_shader &rarch_shader, video_shader &shader, const std::string &configPath);
  static void TranslateShader(const video_shader &shader, rarch_video_shader &rarch_shader, const std::string &configPath);

  static void TranslateRelativePath(char *&absPath, const char *relPath, const std::string &configPath);
  static void TranslateAbsPath(char *relPath, size_t maxPathLen, const char *absPath, const std::string &configPath);

  //! @todo
  static void FreeShader(rarch_video_shader &rarch_shader);
};
