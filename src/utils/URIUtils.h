/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
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
#pragma once

#include <string>
#include <vector>

class CURL;

class URIUtils
{
public:
  URIUtils(void);
  virtual ~URIUtils(void);
/**
   * Convert path to form without duplicated slashes and without relative directories
   * Strip duplicated slashes
   * Resolve and remove relative directories ("/../" and "/./")
   * Will ignore slashes with other direction than specified
   * Will not resolve path starting from relative directory
   * @warning Don't use with "protocol://path"-style URLs
   * @param path string to process
   * @param slashCharacter character to use as directory delimiter
   * @return transformed path
   */
  static std::string CanonicalizePath(const std::string& path, const char slashCharacter = '\\');
};

