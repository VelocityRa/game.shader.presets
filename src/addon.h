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

  /* Loads a config file. Returns NULL if file doesn't exist.
  * NULL path will create an empty config file.
  * Second arg saves its base path.
   */
  virtual config_file_t_* ConfigFileNew(const char *path, const char *basePath) override;

  /* Load a config file from a string. */
  virtual config_file_t_* ConfigFileNewFromString(const char *from_string) override;

  /* Frees config file. */
  virtual void ConfigFileFree(config_file_t_ *conf) override;

   /**
  * ShaderPresetRead:
  * @conf              : Preset file to read from.
  * @shader            : Shader passes handle.
  * @addonPath         : Add-on's path, so that shader source is loaded.
  *                      If nullptr, shader source isn't loaded.
  *
  * Loads preset file and all associated state (passes,
  * textures, imports, etc).
  *
  * Returns: true (1) if successful, otherwise false (0).
  **/
  virtual bool ShaderPresetRead(config_file_t_ *conf, struct video_shader_ *shader) override;

  /**
  * ShaderPresetWrite:
  * @conf              : Preset file to read from.
  * @shader            : Shader passes handle.
  *
  * Saves preset and all associated state (passes,
  * textures, imports, etc) to disk.
  **/
  virtual void ShaderPresetWrite(config_file_t_ *conf, struct video_shader_ *shader) override;

  /**
  * ShaderPresetResolveRelative:
  * @shader            : Shader pass handle.
  * @ref_path          : Relative shader path.
  *
  * Resolves relative shader path (@ref_path) into absolute
  * shader paths.
  **/
  virtual void ShaderPresetResolveRelative(struct video_shader_ *shader, const char *ref_path) override;

  /**
  * ShaderPresetResolveCurrentParameters:
  * @conf              : Preset file to read from.
  * @shader            : Shader passes handle.
  *
  * Reads the current value for all parameters from config file.
  *
  * Returns: true (1) if successful, otherwise false (0).
  **/
  virtual bool ShaderPresetResolveCurrentParameters(config_file_t_ *conf, struct video_shader_ *shader) override;

  /**
  * ShaderPresetResolveParameters:
  * @conf              : Preset file to read from.
  * @shader            : Shader passes handle.
  *
  * Resolves all shader parameters belonging to shaders.
  *
  * Returns: true (1) if successful, otherwise false (0).
  **/
  virtual bool ShaderPresetResolveParameters(config_file_t_ *conf, struct video_shader_ *shader) override;

private:
  void GetAbsolutePassPath(video_shader_pass_& pass, char destPath[]);

  // Base path of shader preset
  std::string m_basePath;
};
