#include "Application.h"
#include "src/Window.h"

Application::Application()
{

}

void Application::Run()
{
    Window window(1600, 1200, "LearnVulkan");  // TODO: Const width and height
    window.Init();

    window.Shutdown();
}