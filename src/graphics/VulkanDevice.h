#pragma once

#include "src/pch/pch.h"

class QueueFamilyIndices;

class VulkanDevice
{
private:
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;  // implicitly destroyed

public:
    VulkanDevice() = default;
    void PickPhysicalDevice(const VkInstance* instance);

private:
    bool IsPhysicalDeviceSuitable(const VkPhysicalDevice& device) const;
    QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device) const;
};

class QueueFamilyIndices
{
public:
    std::optional<uint32_t> graphicsFamily;

    bool IsComplete() const;
};