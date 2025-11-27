# CMakeLists.txt -- CMake build file for Trailmix.

# SPDX-FileType: SOURCE
# SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5)
project(trailmix LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files.
set(TRAILMIX_CPPS
  src/trailmix-main.cpp
  src/trailmix/sys/binpath.cpp
)

# Third-party code being built as separate object files.
#add_subdirectory(src/3rdparty/murmurhash3)

# An extra marker for the source files, to tell what kind of build type we're using.
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type was not specified, switching to 'Debug'.")
  set(CMAKE_BUILD_TYPE Debug)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  message(STATUS "Build type specified as release build.")
  set(RELEASE_BUILD 1)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  message(STATUS "Build type specified as debug build.")
  set(DEBUG_BUILD 1)
else()
  message(FATAL_ERROR "Unrecognized build type!")
endif()

# Determine target platform.
if(WIN32)
  set(TARGET_WINDOWS 1)
  message(STATUS "Windows build environment detected.")
elseif(MINGW)
  set(TARGET_WINDOWS 1)
  set(TARGET_MINGW 1)
  message(STATUS "MinGW build environment detected.")
elseif(APPLE OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(TARGET_APPLE 1)
  message(STATUS "Apple build environment detected.")
elseif(UNIX)
  set(TARGET_LINUX 1)
  message(STATUS "Unix/Linux build environment detected.")
else()
  message(WARNING "Could not determine build environment.")
endif()

# Detect if MinGW is being used to cross-compile to Windows. There are simpler ways, but this way guarantees success when using WSL.
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("
  #ifdef __MINGW32__
    int main() { return 0; }
  #else
    #error Not MinGW
  #endif
" HAVE_MINGW_MACRO)
if (HAVE_MINGW_MACRO)
  set(TARGET_WINDOWS 1)
  set(TARGET_MINGW 1)
  unset(TARGET_LINUX)
  message(STATUS "Extra checks have determined MinGW is being used. Changing target to MinGW/Windows.")
endif()

# Compiler definitions, including target platform and build type.
add_compile_definitions(
  $<$<BOOL:${TARGET_WINDOWS}>:TRAILMIX_TARGET_WINDOWS>
  $<$<BOOL:${TARGET_MINGW}>:TRAILMIX_TARGET_MINGW>
  $<$<BOOL:${TARGET_LINUX}>:TRAILMIX_TARGET_LINUX>
  $<$<BOOL:${TARGET_APPLE}>:TRAILMIX_TARGET_APPLE>
  $<$<BOOL:${RELEASE_BUILD}>:TRAILMIX_BUILD_RELEASE>
  $<$<BOOL:${DEBUG_BUILD}>:TRAILMIX_BUILD_DEBUG>
  __STDC_LIMIT_MACROS
  _USE_MATH_DEFINES
)

# Binary file output. This binary won't actually do anything, it's just to ensure the rest of the code compiles.
add_executable(trailmix ${TRAILMIX_CPPS})
target_link_libraries(trailmix PRIVATE
  ${CMAKE_THREAD_LIBS_INIT}
#  murmurhash3
)

# Include directories.
target_include_directories(trailmix PRIVATE "${CMAKE_SOURCE_DIR}/src")

# Compiler-specific flags.
option(WARNINGS_AS_ERRORS "Turn warnings into errors" OFF)
target_compile_options(trailmix PRIVATE
  # GNU / Clang / Apple Clang
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
    -Wall -Wextra -pedantic -pedantic-errors
    $<$<BOOL:${WARNINGS_AS_ERRORS}>:-Werror>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:Debug>:-g -Og>
  >
  # MSVC
  $<$<CXX_COMPILER_ID:MSVC>:
    /W4 /permissive- /wd4244 /wd4267
    $<$<BOOL:${WARNINGS_AS_ERRORS}>:/WX>
    $<$<CONFIG:Release>:/O2>
    $<$<CONFIG:Debug>:/Od /Zi>
  >
)

# Compiler-specific stripping of symbols.
target_link_options(trailmix PRIVATE
  $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-s>
)

# Windows-specific stuff.
if(TARGET_WINDOWS)
  add_compile_definitions(
    NOMINMAX
    VC_EXTRALEAN
    WIN32_LEAN_AND_MEAN
  )
  target_link_libraries(trailmix PRIVATE
    $<$<BOOL:${TARGET_MINGW}>:mingw32>
	shlwapi
	ntdll
  )
endif(TARGET_WINDOWS)
