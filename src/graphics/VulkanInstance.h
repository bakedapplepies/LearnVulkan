#pragma once

#include <vulkan/vulkan.h>

class VulkanInstance
{
private:
    VkInstance m_vkInstance;
    VkDebugUtilsMessengerEXT m_debugMessenger;

public:
    VulkanInstance() = default;
    void Create();
    void Destroy();
    const VkInstance* GetVKInstance() const;

private:
    void SetupDebugMessenger();
    void PopulateDebugMessengerInfo(VkDebugUtilsMessengerCreateInfoEXT* dbg_messenger_info);
    std::vector<const char*> GetRequiredExtensions();
};