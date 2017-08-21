/*
 *      Copyright (C) 2015-2017 Garrett Brown
 *      Copyright (C) 2015-2017 Team Kodi
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

#include <stdarg.h>
#include <string>
#include <vector>

namespace SHADER
{
  class StringUtils
  {
  public:
    /*!
     * \brief Transform characters to create a safe URL
     * \param str The string to transform
     * \return The transformed string, with unsafe characters replaced by "_"
     *
     * Safe URLs are composed of the unreserved characters defined in
     * RFC 3986 section 2.3:
     *
     *   ALPHA / DIGIT / "-" / "." / "_" / "~"
     *
     * Characters outside of this set will be replaced by "_".
     */
    static std::string MakeSafeUrl(const std::string& str);

    /*!
     * \brief Transform characters to create a safe, printable string
     * \param str The string to transform
     * \return The transformed string, with unsafe characters replaced by " "
     *
     * Unsafe characters are defined as the non-printable ASCII characters
     * (character code 0-31).
     */
    static std::string MakeSafeString(std::string str);

    static std::string& Trim(std::string& str);
    static std::string& TrimLeft(std::string& str);
    static std::string& TrimRight(std::string& str);

    static std::string& Trim(std::string& str, const char* chars);
    static std::string& TrimLeft(std::string& str, const char* chars);
    static std::string& TrimRight(std::string& str, const char* chars);

    static bool EndsWith(const std::string& str, const std::string& suffix);

    /*!
     * \brief Get a formatted string similar to sprintf
     *
     * Beware that this does not support directly passing in
     * std::string objects. You need to call c_str() to pass
     * the const char* buffer representing the value of the
     * std::string object.
     *
     * \param fmt Format of the resulting string
     * \param ... variable number of value type arguments
     * \return Formatted string
    */
    static std::string Format(const char* fmt, ...);
    static std::string FormatV(const char* fmt, va_list args);

    /*! \brief Split a string by the specified delimiters.
    Splits a string using one or more delimiting characters, ignoring empty tokens.
    Differs from Split() in two ways:
    1. The delimiters are treated as individual characters, rather than a single delimiting string.
    2. Empty tokens are ignored.
    \return a vector of tokens
    */
    static void Tokenize(const std::string& input, std::vector<std::string>& tokens, const std::string& delimiters);

    template<typename CONTAINER>
    static std::string Join(const CONTAINER &strings, const std::string& delimiter)
    {
       std::string result;
       for (const auto& str : strings)
          result += str + delimiter;

       if (!result.empty())
          result.erase(result.size() - delimiter.size());
       return result;
    }

    static int Replace(std::string &str, char oldChar, char newChar);
  };
}
