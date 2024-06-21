#include "VulkanDevice.h"

void VulkanDevice::PickPhysicalDevice(const VkInstance* instance)
{
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);

    assert(deviceCount > 0 && "Failed to find GPU with Vulkan support.");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(*instance, &deviceCount, devices.data());

    for (const VkPhysicalDevice& device : devices)
    {
        if (IsPhysicalDeviceSuitable(device))
        {
            m_physicalDevice = device;
            break;
        }
    }
    assert(m_physicalDevice != VK_NULL_HANDLE && "Failed to find a suitable GPU.");
}

bool VulkanDevice::IsPhysicalDeviceSuitable(const VkPhysicalDevice& device) const
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    // TODO: Implement GPU Rating

    QueueFamilyIndices queueIndices = FindQueueFamilies(device);

    // Any GPU that can handle Vulkan and graphics is fine for now
    return queueIndices.IsComplete();
}

QueueFamilyIndices VulkanDevice::FindQueueFamilies(const VkPhysicalDevice& device) const
{
    QueueFamilyIndices familyIndices;

    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    
    std::vector<VkQueueFamilyProperties> queueFamiliesProperties;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamiliesProperties.data());

    uint32_t i = 0;
    for (const VkQueueFamilyProperties& queueFamilyProperty : queueFamiliesProperties)
    {
        if (queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            familyIndices.graphicsFamily = i;
        }
        if (familyIndices.IsComplete()) break;  // Enough queues checked
        i++;
    }

    return familyIndices;
}

bool QueueFamilyIndices::IsComplete() const
{
    return graphicsFamily.has_value();
}