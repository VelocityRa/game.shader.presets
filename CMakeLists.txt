cmake_minimum_required(VERSION 3.1)
project(game.resource.shader.presets)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(CheckIncludeFiles)

# --- Add-on Dependencies ------------------------------------------------------

find_package(Kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(p8-platform REQUIRED)

include_directories(${INCLUDES}
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
                     src/utils/StringUtils.cpp)

set(SHADERPRESETS_HEADERS src/addon.h
                     src/filesystem/DirectoryCache.h
                     src/filesystem/DirectoryUtils.h
                     src/filesystem/Filesystem.h
                     src/filesystem/FilesystemTypes.h
                     src/filesystem/FileUtils.h
                     src/filesystem/IDirectoryUtils.h
                     src/filesystem/IFile.h
                     src/filesystem/IFileUtils.h
                     src/filesystem/generic/ReadableFile.h
                     src/filesystem/generic/SeekableFile.h
                     src/filesystem/vfs/VFSDirectoryUtils.h
                     src/filesystem/vfs/VFSFileUtils.h
                     src/log/ILog.h
                     src/log/LogAddon.h
                     src/log/LogConsole.h
                     src/log/Log.h
                     src/utils/CommonIncludes.h
                     src/utils/CommonMacros.h
                     src/utils/StringUtils.h)

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


build_addon(game.resource.shader.presets SHADERPRESETS DEPLIBS)

# ------------------------------------------------------------------------------
