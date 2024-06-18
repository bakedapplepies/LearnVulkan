cmake_minimum_required(VERSION 3.26.0)
project(VulkanTest CXX C)

add_subdirectory(vendor)
add_subdirectory(src)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_options(-O0 -fsanitize=address -g)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -fsanitize=address -g)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-O3)
    add_link_options(-O3)
endif()