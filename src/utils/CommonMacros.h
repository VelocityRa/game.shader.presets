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
#pragma once

#if !defined(ASSERT)
  #if defined(DEBUG) || defined(_DEBUG)
    #include <assert.h>
    #define ASSERT(x)  assert(x)
  #else
    #define ASSERT(x)
  #endif
#endif

#if !defined(SAFE_DELETE)
  #define SAFE_DELETE(x)  do { delete (x); (x) = NULL; } while (0)
#endif

#if !defined(SAFE_DELETE_ARRAY)
  #define SAFE_DELETE_ARRAY(x)  do { delete[] (x); (x) = NULL; } while (0)
#endif

#if !defined(SAFE_RELEASE)
  #define SAFE_RELEASE(p)  do { if(p) { (p)->Release(); (p)=NULL; } } while (0)
#endif

#ifndef CONSTRAIN
  // Credit: https://stackoverflow.com/questions/8941262/constrain-function-port-from-arduino
  #define CONSTRAIN(amt, low, high)  ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#endif

#ifndef ARRAY_SIZE
  #define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))
#endif

#ifndef MIN
  #define MIN(x, y)  ((y) < (x) ? (y) : (x))
#endif

#ifndef MAX
  #define MAX(x, y)  ((y) > (x) ? (y) : (x))
#endif
