/*
 *      Copyright (C) 2005-2015 Team Kodi
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
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "URIUtils.h"
#include "StringUtils.h"

#include <cassert>

std::string URIUtils::CanonicalizePath(const std::string& path, const char slashCharacter /*= '\\'*/)
{
  assert(slashCharacter == '\\' || slashCharacter == '/');

  if (path.empty())
    return path;

  const std::string slashStr(1, slashCharacter);
  std::vector<std::string> pathVec, resultVec;
  SHADER::StringUtils::Tokenize(path, pathVec, slashStr);

  for (std::vector<std::string>::const_iterator it = pathVec.begin(); it != pathVec.end(); ++it)
  {
    if (*it == ".")
    { /* skip - do nothing */ }
    else if (*it == ".." && !resultVec.empty() && resultVec.back() != "..")
      resultVec.pop_back();
    else
      resultVec.push_back(*it);
  }

  std::string result;
  if (path[0] == slashCharacter)
    result.push_back(slashCharacter); // add slash at the begin

  result += SHADER::StringUtils::Join(resultVec, slashStr);

  if (path[path.length() - 1] == slashCharacter  && !result.empty() && result[result.length() - 1] != slashCharacter)
    result.push_back(slashCharacter); // add slash at the end if result isn't empty and result isn't "/"

  return result;
}
