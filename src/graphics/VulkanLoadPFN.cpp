#include "VulkanLoadPFN.h"

// template <typename T_PFN>
// auto GetPFN(VkInstance* instance, const char* func_name)
// {
//     auto func = (T_PFN)vkGetInstanceProcAddr(*instance, func_name);

//     if (func != nullptr)
//     {
//         return func;
//     }
//     else
//     {
//         assert(false);
//     }
// }