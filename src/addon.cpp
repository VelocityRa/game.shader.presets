/*
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

#define PERIPHERAL_ADDON_JOYSTICKS

#include "addon.h"
#include "filesystem/Filesystem.h"
#include "log/Log.h"
#include "log/LogAddon.h"
#include "utils/CommonIncludes.h"
#include "utils/CommonMacros.h"

#include <algorithm>
#include <vector>

using namespace JOYSTICK;


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

ADDONCREATOR(CShaderPreset) // Don't touch this!
