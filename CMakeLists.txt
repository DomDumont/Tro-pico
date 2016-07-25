Project (Tro-pico)

cmake_minimum_required (VERSION 2.8.6)

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
ENDIF(WIN32)


add_subdirectory (Sources)