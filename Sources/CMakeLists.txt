file(GLOB_RECURSE TRO-PICO_SOURCES "*.cpp")
file(GLOB_RECURSE TRO-PICO_HEADERS "*.h")



if (NOT DEFINED EMSCRIPTEN)
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIR})
	message( "SDL2 include path found = " ${SDL2_INCLUDE_DIR})
endif()



add_executable (Tro-pico ${TRO-PICO_SOURCES} ${TRO-PICO_HEADERS})

target_link_libraries(Tro-pico ${SDL2_LIBRARY})

INSTALL(TARGETS Tro-pico DESTINATION Tro-pico)


