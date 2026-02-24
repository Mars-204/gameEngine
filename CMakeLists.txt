# CMakeList.txt : CMake project for ge, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("gameEngine")

# Add source to this project's executable.
add_executable (gameEngine "external/glad/include/glad/glad.h" 
			"external/glad/include/KHR/khrplatform.h" "external/glad/src/glad.c"
			"external/glfw/include/GLFW/glfw3.h" "external/glfw/include/GLFW/glfw3native.h"
			"src/main.cpp")

# TODO: Add tests and install targets if needed.
target_include_directories(gameEngine PRIVATE 
			${CMAKE_SOURCE_DIR}/external/glad/include
			${CMAKE_SOURCE_DIR}/external/glfw/include
			)

target_link_directories(gameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/external/glfw/lib-vc2019
)

target_link_libraries(gameEngine
    glfw3
    opengl32
)