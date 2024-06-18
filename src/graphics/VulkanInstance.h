#pragma once

#include <vulkan/vulkan.h>

class VulkanInstance
{
private:
    VkInstance m_vkInstance;

public:
    VulkanInstance();
};