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
#include <kodi/AddonBase.h>

struct rarch_video_shader;

class ATTRIBUTE_HIDDEN CShaderPreset
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
  preset_file PresetFileNew(const char *path) override;
  void PresetFileFree(preset_file file) override;
  bool ShaderPresetRead(preset_file file, video_shader &shader) override;
  void ShaderPresetWrite(preset_file file, const video_shader &shader) override;
  //void ShaderPresetResolveRelative(video_shader &shader, const char *ref_path) override;
  //bool ShaderPresetResolveCurrentParameters(preset_file file, video_shader &shader) override;
  bool ShaderPresetResolveParameters(preset_file file, video_shader &shader) override;
  void ShaderPresetFree(video_shader &shader) override;
};
