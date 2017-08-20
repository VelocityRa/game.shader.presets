cmake_minimum_required(VERSION 3.1)
project(game.shader.presets)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(CheckIncludeFiles)

# --- Add-on Dependencies ------------------------------------------------------

find_package(Kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(p8-platform REQUIRED)

include_directories(${INCLUDES}
                    ${PROJECT_SOURCE_DIR}/src/depends/libretro-common/include
                    ${PROJECT_SOURCE_DIR}/src/depends
                    ${PROJECT_SOURCE_DIR}/src
                    ${KODI_INCLUDE_DIR}/.. # Hack way with "/..", need bigger Kodi cmake rework to match right include ways (becomes done in future)
                    ${kodiplatform_INCLUDE_DIRS}
                    ${p8-platform_INCLUDE_DIRS})

set(SHADERPRESETS_SOURCES src/addon.cpp
                     src/filesystem/DirectoryCache.cpp
                     src/filesystem/DirectoryUtils.cpp
                     src/filesystem/Filesystem.cpp
                     src/filesystem/FileUtils.cpp
                     src/filesystem/generic/ReadableFile.cpp
                     src/filesystem/generic/SeekableFile.cpp
                     src/filesystem/vfs/VFSDirectoryUtils.cpp
                     src/filesystem/vfs/VFSFileUtils.cpp
                     src/log/Log.cpp
                     src/log/LogAddon.cpp
                     src/log/LogConsole.cpp
                     src/utils/RarchTranslator.cpp
                     src/utils/StringUtils.cpp
                     src/utils/URIUtils.cpp
                     
                     src/depends/file_path_special.c
                     src/depends/gfx/video_shader_parse.c
                     src/depends/gfx/video_state_tracker.c
                     src/depends/libretro-common/compat/compat_posix_string.c
                     src/depends/libretro-common/compat/compat_strcasestr.c
                     src/depends/libretro-common/compat/compat_strl.c
                     src/depends/libretro-common/file/config_file.c
                     src/depends/libretro-common/file/file_path.c
                     src/depends/libretro-common/file/retro_stat.c
                     src/depends/libretro-common/hash/rhash.c
                     src/depends/libretro-common/lists/string_list.c
                     src/depends/libretro-common/streams/file_stream.c
                     src/depends/libretro-common/string/stdstring.c)

set(SHADERPRESETS_HEADERS src/addon.h
                     src/filesystem/DirectoryCache.h
                     src/filesystem/DirectoryUtils.h
                     src/filesystem/Filesystem.h
                     src/filesystem/FilesystemTypes.h
                     src/filesystem/FileUtils.h
                     src/filesystem/generic/ReadableFile.h
                     src/filesystem/generic/SeekableFile.h
                     src/filesystem/IDirectoryUtils.h
                     src/filesystem/IFile.h
                     src/filesystem/IFileUtils.h
                     src/filesystem/vfs/VFSDirectoryUtils.h
                     src/filesystem/vfs/VFSFileUtils.h
                     src/log/ILog.h
                     src/log/Log.h
                     src/log/LogAddon.h
                     src/log/LogConsole.h
                     src/utils/CommonIncludes.h
                     src/utils/CommonMacros.h
                     src/utils/RarchTranslator.h
                     src/utils/StringUtils.h
                     src/utils/URIUtils.h
                     
                     src/depends/file_path_special.h
                     src/depends/gfx/video_shader_parse.h
                     src/depends/gfx/video_state_tracker.h
                     src/depends/libretro-common/include/boolean.h
                     src/depends/libretro-common/include/compat/msvc.h
                     src/depends/libretro-common/include/compat/posix_string.h
                     src/depends/libretro-common/include/compat/strcasestr.h
                     src/depends/libretro-common/include/compat/strl.h
                     src/depends/libretro-common/include/file/config_file.h
                     src/depends/libretro-common/include/file/file_path.h
                     src/depends/libretro-common/include/lists/string_list.h
                     src/depends/libretro-common/include/retro_assert.h
                     src/depends/libretro-common/include/retro_stat.h
                     src/depends/libretro-common/include/retro_common_api.h
                     src/depends/libretro-common/include/retro_inline.h
                     src/depends/libretro-common/include/retro_miscellaneous.h
                     src/depends/libretro-common/include/rhash.h
                     src/depends/libretro-common/include/streams/file_stream.h
                     src/depends/libretro-common/include/string/stdstring.h)

if(CORE_SYSTEM_NAME STREQUAL windows)
  list(APPEND SHADERPRESETS_SOURCES src/utils/windows/CharsetConverter.cpp)
  list(APPEND SHADERPRESETS_HEADERS src/utils/windows/CharsetConverter.h)
endif()

check_include_files("syslog.h" HAVE_SYSLOG)

if(HAVE_SYSLOG)
  list(APPEND SHADERPRESETS_SOURCES src/log/LogSyslog.cpp)
  list(APPEND SHADERPRESETS_HEADERS src/log/LogSyslog.h)
endif()

list(APPEND DEPLIBS ${kodiplatform_LIBRARIES}
                    ${p8-platform_LIBRARIES})


build_addon(game.shader.presets SHADERPRESETS DEPLIBS)
