#pragma once

#include "src/pch/pch.h"
#include "src/graphics/VulkanInstance.h"
#include "src/graphics/VulkanDevice.h"

class Window
{
private:
    // ----- Windowing -----
    GLFWwindow* m_window = nullptr;  // nullptr or glfwDestroyWindow will throw a tantrum with asan
    uint32_t    m_width;
    uint32_t    m_height;
    const char* m_window_name;

    // ----- Vulkan -----
    VulkanInstance m_vulkanInstance;
    VulkanDevice   m_vulkanDevice;

public:
    Window(uint32_t width, uint32_t height, const char* window_name);
    void Init();
    void Shutdown();

private:
    void VulkanInit();
    void VulkanCleanUp();
};