cmake_minimum_required(VERSION 3.26.0)
project(${CMAKE_PROJECT_NAME} CXX C)

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" FORCE )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" FORCE )
add_subdirectory(glfw)

add_subdirectory(glm)

add_subdirectory(fmt)