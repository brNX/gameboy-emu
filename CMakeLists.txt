cmake_minimum_required(VERSION 2.6)

project (Gameboy-Emu)

# another list, this time it includes all header files that should be treated with moc
SET( MOC_HDRS
     mainwindow.h
)

## some .ui files
SET( UIS
    mainwindow.ui
)

## and finally an resource file
#SET( RCS
#     ./src/rc/sample.qrc
#)

# The version number.
set (Gameboy-Emu_VERSION_MAJOR 1)
set (Gameboy-Emu_VERSION_MINOR 0)

# by default only QtCore and QtGui modules are enabled
# other modules must be enabled like this:
#SET( QT_USE_QT3SUPPORT TRUE )
SET( QT_USE_QTTEST TRUE )
SET( QT_USE_QTGUI TRUE )

# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
FIND_PACKAGE( Qt4 REQUIRED )


# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
INCLUDE( ${QT_USE_FILE} )

# additional compiler flags
#add_definitions(-Wall )

if (UNIX)
    set (CMAKE_C_FLAGS_DEBUG "-g3 -Wall -pg")
    set (CMAKE_C_FLAGS_RELEASE "-march=native -03")
    set (CMAKE_CXX_FLAGS_DEBUG "-g3 -Wall -pg")
    set (CMAKE_CXX_FLAGS_RELEASE "-march=native -03")
    set (CMAKE_LD_FLAGS_DEBUG "-g3 -Wall -pg")
endif(UNIX)

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
QT4_ADD_RESOURCES( RC_SRC ${RCS} )

# this will run uic on .ui files:
QT4_WRAP_UI( UI_HDRS ${UIS} )

# and finally this will run moc:
QT4_WRAP_CPP( MOC_SRCS ${MOC_HDRS} )

# here we instruct CMake to build "sample" executable from all of the source files
add_executable(Gameboy-Emu ${MOC_SRCS} ${RC_SRCS} ${UI_HDRS} mainwindow.h mainwindow.cpp lcd.h lcd.c no_sillywarnings.h types.h Z80.c Z80.h memory.c memory.h cartridge.h cartridge.c lookuptables.h debugcounters.h Opcodes.h main.cpp)

# last thing we have to do is to tell CMake what libraries our executable needs,
# luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
TARGET_LINK_LIBRARIES(Gameboy-Emu ${QT_LIBRARIES})

ADD_DEFINITIONS(-DQT_DEBUG)


###########unit testing###############

SET( SAMPLE_SRCS_UNIT
    ld_test.cpp
)

SET( SAMPLE_MOC_HDRS_UNIT
     ld_test.h
)

# and finally this will run moc:
QT4_WRAP_CPP( SAMPLE_MOC_SRCS_UNIT ${SAMPLE_MOC_HDRS_UNIT} )

add_executable(Gameboy-Unit ${SAMPLE_SRCS_UNIT} ${SAMPLE_MOC_SRCS_UNIT} ${SAMPLE_RC_SRCS_UNIT} lcd.h lcd.c no_sillywarnings.h types.h Z80.c Z80.h cartridge.h cartridge.c memory.c memory.h lookuptables.h debugcounters.h Opcodes.h)

TARGET_LINK_LIBRARIES(
   Gameboy-Unit
   ${QT_LIBRARIES}
   ${QT_QTTEST_LIBRARIES}
)
