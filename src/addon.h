#pragma once
/*
 *      Copyright (C) 2017      Nick Renieris
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

  // CAddonBase overrides

  virtual ADDON_STATUS Create() override;
  virtual ADDON_STATUS GetStatus() override;
  virtual ADDON_STATUS SetSetting(const std::string& settingName, const kodi::CSettingValue& settingValue) override;

  // CInstanceShaderPreset overrides

  virtual config_file_t_* ConfigFileNew(const char *path) override;
  virtual config_file_t_* ConfigFileNewFromString(const char *from_string) override;
  virtual void ConfigFileFree(config_file_t_ *conf) override;

  virtual bool ShaderPresetRead(config_file_t_ *conf, struct video_shader_ *shader) override;
  virtual void ShaderPresetWrite(config_file_t_ *conf, struct video_shader_ *shader) override;
  virtual void ShaderPresetResolveRelative(struct video_shader_ *shader, const char *ref_path) override;
  virtual bool ShaderPresetResolveCurrentParameters(config_file_t_ *conf, struct video_shader_ *shader) override;
  virtual bool ShaderPresetResolveParameters(config_file_t_ *conf, struct video_shader_ *shader) override;
};
