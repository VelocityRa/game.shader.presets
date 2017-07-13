#pragma once
/*
 *      Copyright (C) 2017 Nick Renieris
 *      Copyright (C) 2014-2015 Garrett Brown
 *      Copyright (C) 2014-2015 Team XBMC
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <kodi/addon-instance/ShaderPreset.h>

#include "depends/gfx/video_shader_parse.h"

class CShaderPreset
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceShaderPreset
{
public:
  CShaderPreset() {}
  virtual ~CShaderPreset();

  virtual ADDON_STATUS Create() override;
  virtual ADDON_STATUS GetStatus() override;
  virtual ADDON_STATUS SetSetting(const std::string& settingName, const kodi::CSettingValue& settingValue) override;

  // ===============================================

  virtual int GetTest(unsigned int test_arg) override;

  // TODO: Apply Kodi code styling to function names
  
  virtual config_file_t_* wrapper_config_file_new(const char *path) override;
  virtual config_file_t_* wrapper_config_file_new_from_string(const char *from_string) override;
  virtual void wrapper_config_file_free(config_file_t_ *conf) override;

  virtual bool wrapper_video_shader_read_conf_path_cgp(const char *conf_path, struct video_shader_ **shader) override;
  virtual bool wrapper_video_shader_read_conf_cgp(config_file_t_ *conf, struct video_shader_ **shader) override;
  virtual void wrapper_video_shader_write_conf_cgp(config_file_t_ *conf, struct video_shader_ *shader) override;
  virtual void wrapper_video_shader_resolve_relative(struct video_shader_ *shader, const char *ref_path) override;
  virtual bool wrapper_video_shader_resolve_current_parameters(config_file_t_ *conf, struct video_shader_ *shader) override;
  virtual bool wrapper_video_shader_resolve_parameters(config_file_t_ *conf, struct video_shader_ *shader) override;
};
