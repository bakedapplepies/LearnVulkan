cmake_minimum_required(VERSION 3.26.0)
project(${CMAKE_PROJECT_NAME} CXX C)

set(SOURCE_FILES
    Application.cpp
    Window.cpp
    main.cpp
)

set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/FMT/include
)

set(PCH
    ${CMAKE_SOURCE_DIR}/src/pch/pch.h
    ${CMAKE_SOURCE_DIR}/src/pch/pch.cpp
)

add_subdirectory(graphics)

add_executable(${CMAKE_PROJECT_NAME}
    ${SOURCE_FILES}
)

target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE ${PCH})
target_precompile_headers(${CMAKE_PROJECT_NAME}.Graphics PRIVATE ${PCH})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
target_include_directories(${CMAKE_PROJECT_NAME}.Graphics PRIVATE ${INCLUDE_DIRECTORIES})

target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)
target_link_libraries(${CMAKE_PROJECT_NAME}
    glfw
    vulkan-1
    fmt::fmt
    gdi32
    user32
    kernel32
    shell32

    ${CMAKE_PROJECT_NAME}.Graphics
)