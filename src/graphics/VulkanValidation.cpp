#include "VulkanValidation.h"

bool VulkanValidation::CheckValidationLayerSupport() const
{
    // ----- Get all available layers -----
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // ----- Check if required layers are available -----
    for (const char* requiredLayer : VALIDATION_LAYERS)
    {
        bool requiredLayerFound = false;
        for (const auto& layerProperty : availableLayers)
        {
            if (strcmp(requiredLayer, layerProperty.layerName) == 0)  // 0 is equal
            {
                requiredLayerFound = true;
                break;
            }
        }

        if (!requiredLayerFound)
        {
            return false;
        }
    }

    return true;
}