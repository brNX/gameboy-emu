cmake_minimum_required(VERSION 2.6)

project (Gameboy-Emu)

# with SET() command you can change variables or define new ones
# here we define SAMPLE_SRCS variable that contains a list of all .cpp files
# note that we don't need \ at the end of line
SET( SAMPLE_SRCS_UNIT
    ld_test.cpp
)

# another list, this time it includes all header files that should be treated with moc
SET( SAMPLE_MOC_HDRS_UNIT
     ld_test.h
)

## some .ui files
SET( SAMPLE_UIS_UNIT
)

## and finally an resource file
#SET( SAMPLE_RCS
#     ./src/rc/sample.qrc
#)

# The version number.
set (Gameboy-Emu_VERSION_MAJOR 1)
set (Gameboy-Emu_VERSION_MINOR 0)

# by default only QtCore and QtGui modules are enabled
# other modules must be enabled like this:
#SET( QT_USE_QT3SUPPORT TRUE )
SET( QT_USE_QTTEST TRUE )
SET( QT_DONT_USE_QTGUI TRUE )

# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
FIND_PACKAGE( Qt4 REQUIRED )


# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
INCLUDE( ${QT_USE_FILE} )

# additional compiler flags
add_definitions(-Wall )

set (CMAKE_C_FLAGS_DEBUG "-g3 -O0 -Wall")
set (CMAKE_C_FLAGS_RELEASE "-march=native -03") 
set (CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -Wall")
set (CMAKE_CXX_FLAGS_RELEASE "-march=native -03") 

#set (CMAKE_C_COMPILER "clang")
#set (CMAKE_CXX_COMPILER "clang++")

set (CMAKE_BUILD_TYPE Debug)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/GameboyConfig.h.in"
  "${PROJECT_BINARY_DIR}/GameboyConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
INCLUDE_DIRECTORIES(
   ${PROJECT_BINARY_DIR}
   ${QT_INCLUDE_DIR}
   ${QT_QTTEST_INCLUDE_DIR}
)

# this command will generate rules that will run rcc on all files from SAMPLE_RCS
# in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES( SAMPLE_RC_SRC_SUNIT ${SAMPLE_RCS_UNIT} )

# this will run uic on .ui files:
QT4_WRAP_UI( SAMPLE_UI_HDRS_UNIT ${SAMPLE_UIS_UNIT} )

# and finally this will run moc:
QT4_WRAP_CPP( SAMPLE_MOC_SRCS_UNIT ${SAMPLE_MOC_HDRS_UNIT} )

# here we instruct CMake to build "sample" executable from all of the source files
add_executable(Gameboy-Emu ${SAMPLE_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_RC_SRCS} ${SAMPLE_UI_HDRS} lcd.h lcd.c no_sillywarnings.h types.h Z80.c Z80.h memory.c memory.h cartridge.h cartridge.c lookuptables.h debugcounters.h Opcodes.h main.cpp)

add_executable(Gameboy-Unit ${SAMPLE_SRCS_UNIT} ${SAMPLE_MOC_SRCS_UNIT} ${SAMPLE_RC_SRCS_UNIT} ${SAMPLE_UI_HDRS_UNIT} lcd.h lcd.c no_sillywarnings.h types.h Z80.c Z80.h cartridge.h cartridge.c memory.c memory.h lookuptables.h debugcounters.h Opcodes.h)

# last thing we have to do is to tell CMake what libraries our executable needs,
# luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
TARGET_LINK_LIBRARIES(Gameboy-Emu ${QT_LIBRARIES} )

ADD_DEFINITIONS(-DQT_DEBUG)

TARGET_LINK_LIBRARIES(
   Gameboy-Unit
   ${QT_LIBRARIES}
   ${QT_QTTEST_LIBRARIES}
)
