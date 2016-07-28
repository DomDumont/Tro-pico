Project (Tro-pico)

cmake_minimum_required (VERSION 2.8.6)

set(PRODUCT_NAME "Tro-pico")
set(COMPANY_NAME "Deliriom")
set(PRODUCT_DESCRIPTION "Tiny Replica of Pico")


find_package(Git)
if(GIT_FOUND)
	MESSAGE("Git was found :-)")
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe
            OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
            OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

MESSAGE(${GIT_DESCRIBE_VERSION})

 # extract major minor and patch from Git version
string(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" VERSION_MAJOR "${GIT_DESCRIBE_VERSION}")
string(REGEX REPLACE "^[0-9]+\\.([0-9]+)\\.[0-9]+.*" "\\1" VERSION_MINOR "${GIT_DESCRIBE_VERSION}")
string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${GIT_DESCRIBE_VERSION}")


if (WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set(TARGET_WIN32 1)
	add_definitions(-DTARGET_WIN32)
endif(WIN32)

if (UNIX)
	set(TARGET_LINUX 1)
	add_definitions(-DTARGET_LINUX)
endif(UNIX)

if (APPLE)
	set(TARGET_OSX 1)
	add_definitions(-DTARGET_OSX)
endif(APPLE)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Sources/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Sources/config.h @ONLY)
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h


IF(NOT WIN32)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
	        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif()
endif()


set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

IF(WIN32)
	MESSAGE("Set SDL2 Env variable on Win32 platforms")
	SET(ENV{SDL2} ${CMAKE_SOURCE_DIR}/Extern/SDL2-2.0.4)
	SET(ENV{GLEW_ROOT_PATH} ${CMAKE_SOURCE_DIR}/Extern/glew-2.0.0)
ENDIF(WIN32)



add_subdirectory (Sources)





SET(CPACK_GENERATOR "ZIP")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Dominique Dumont") #required
SET(CPACK_PACKAGE_VERSION "${GIT_DESCRIBE_VERSION}")
SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}") 
INCLUDE(CPack)