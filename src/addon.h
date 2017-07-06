#pragma once
/*
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

  // virtual void GetCapabilities(PERIPHERAL_CAPABILITIES &capabilities) override;
  // virtual PERIPHERAL_ERROR PerformDeviceScan(unsigned int* peripheral_count, PERIPHERAL_INFO** scan_results) override;

  // ...

private:
  // ...
};
