#pragma once

#include <vulkan/vulkan.h>

#ifdef NDEBUG
    const bool ENABLE_VALIDATION_LAYERS = false;
#else
    const bool ENABLE_VALIDATION_LAYERS = true;
#endif

const std::vector<const char*> VALIDATION_LAYERS = {
    "VK_LAYER_KHRONOS_validation"
};

class VulkanValidation
{
public:
    VulkanValidation() = default;
    bool CheckValidationLayerSupport() const;
};