#include "Window.h"

Window::Window(uint32_t width, uint32_t height, const char* window_name)
    : m_width(width), m_height(height), m_window_name(window_name)
{

}

void Window::Init()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* m_window = glfwCreateWindow(m_width, m_height, m_window_name, nullptr, nullptr);

    VulkanInit();
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
    }
    VulkanCleanUp();
    
}

void Window::VulkanInit()
{
    m_vulkanInstance.Create();
    m_vulkanDevice.PickPhysicalDevice(m_vulkanInstance.GetVKInstance());
}

void Window::VulkanCleanUp()
{
    m_vulkanInstance.Destroy();
    // VulkanDevice is deleted implicitly
}

void Window::Shutdown()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}