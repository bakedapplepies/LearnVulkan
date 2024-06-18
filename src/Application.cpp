#include "Application.h"
#include "src/Window.h"
#include "src/graphics/VulkanInstance.h"

Application::Application()
{

}

void Application::Run()
{
    Window window(1600, 1200, "LearnVulkan");  // TODO: Const width and height
    window.Init();

    VulkanInstance vulkanInstance;

    window.Shutdown();
}