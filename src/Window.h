#pragma once

#include "src/pch/pch.h"

class Window
{
private:
    GLFWwindow* m_window = nullptr;  // nullptr or glfwDestroyWindow will throw a tantrum with asan
    uint32_t m_width;
    uint32_t m_height;
    const char* m_window_name;

public:
    Window(uint32_t width, uint32_t height, const char* window_name);
    void Init();
    void Shutdown();
};