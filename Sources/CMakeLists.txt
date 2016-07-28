file(GLOB_RECURSE TRO-PICO_SOURCES "*.cpp")
file(GLOB_RECURSE TRO-PICO_HEADERS "*.h")



if (NOT DEFINED EMSCRIPTEN)
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIR})
	message( "SDL2 include path found = " ${SDL2_INCLUDE_DIR})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	MESSAGE("GLEW include path found = " ${GLEW_INCLUDE_PATH})
    include_directories(${GLEW_INCLUDE_PATH})
    link_libraries(${GLEW_LIBRARY})
endif()

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
endif()

include_directories("../Extern/stb")


add_executable (Tro-pico ${TRO-PICO_SOURCES} ${TRO-PICO_HEADERS})

target_link_libraries(Tro-pico ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

INSTALL(TARGETS Tro-pico DESTINATION Tro-pico)


