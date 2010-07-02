cmake_minimum_required(VERSION 2.6)

project (Gameboy-Emu)

# The version number.
set (Gameboy-Emu_VERSION_MAJOR 1)
set (Gameboy-Emu_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/GameboyConfig.h.in"
  "${PROJECT_BINARY_DIR}/GameboyConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


add_executable(Gameboy-Emu Z80.c Z80.h memory.c memory.h lookuptables.h main.cpp)