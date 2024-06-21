#pragma once

#include <vulkan/vulkan.h>
#include <type_traits>
#include <functional>

template <typename T_PFN>
T_PFN Get_EXT_PFN(VkInstance* instance, const char* pfn_str)
{
    auto func = (T_PFN)vkGetInstanceProcAddr(*instance, pfn_str);

    if (func != nullptr)
    {
        return func;
    }
    else
    {
        assert(false);
    }
}