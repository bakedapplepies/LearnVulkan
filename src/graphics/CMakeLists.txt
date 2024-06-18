cmake_minimum_required(VERSION 3.26.0)
project(${CMAKE_PROJECT_NAME}.Graphics CXX C)

set(SOURCE_FILES
    VulkanInstance.cpp
)

add_library(${CMAKE_PROJECT_NAME}.Graphics ${SOURCE_FILES})