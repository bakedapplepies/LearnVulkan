#include "VulkanInstance.h"
#include "src/graphics/VulkanValidation.h"
#include "src/graphics/VulkanLoadPFN.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
);

void VulkanInstance::Create()
{
    // ----- Check validation layer -----
    VulkanValidation vulkanValidation;
    if (ENABLE_VALIDATION_LAYERS && !vulkanValidation.CheckValidationLayerSupport())
    {
        assert(false && "Enabled validation layers but not available.");
    }

    // ----- Driver Info -----
    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Learn Vulkan";
    appInfo.pNext = nullptr;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    // ----- Get extensions -----
    std::vector<const char*> requiredExtensions = GetRequiredExtensions();
    fmt::print("Required extensions: {}\n", requiredExtensions.size());
    for (uint32_t i = 0; i < requiredExtensions.size(); i++)
    {
        fmt::print("\t{}\n", requiredExtensions[i]);
    }

    uint32_t supportedExtensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, nullptr);
    std::vector<VkExtensionProperties> supportedExtensions(supportedExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, supportedExtensions.data());
    fmt::print("Supported extensions: {}\n", supportedExtensionCount);
    for (const auto& i : supportedExtensions)
    {
        fmt::print("\t{}\n", i.extensionName);
    }

    // ----- Instance Info -----
    VkInstanceCreateInfo instanceInfo;
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    instanceInfo.ppEnabledExtensionNames = requiredExtensions.data();

    // Debug messenger for creation and deletion of VkInstance
    VkDebugUtilsMessengerCreateInfoEXT dbgMessengerInfo;
    if (ENABLE_VALIDATION_LAYERS)
    {
        instanceInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
        instanceInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());

        PopulateDebugMessengerInfo(&dbgMessengerInfo);
        instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&dbgMessengerInfo;
    }
    else
    {
        instanceInfo.enabledLayerCount = 0;
        instanceInfo.pNext = nullptr;
    }

    VkResult result = vkCreateInstance(&instanceInfo, nullptr, &m_vkInstance);
    if (result != VK_SUCCESS)
    {
        assert(false && "Failed to create Vulkan instance.");
    }

    // ----- Setup Debug messenger for whole program -----
    SetupDebugMessenger();
}

void VulkanInstance::Destroy()
{
    auto vkDestroyDebugUtilsMessengerEXT =
        Get_EXT_PFN<PFN_vkDestroyDebugUtilsMessengerEXT>(&m_vkInstance, "vkDestroyDebugUtilsMessengerEXT");
    vkDestroyDebugUtilsMessengerEXT(m_vkInstance, m_debugMessenger, nullptr);
    vkDestroyInstance(m_vkInstance, nullptr);
}

std::vector<const char*> VulkanInstance::GetRequiredExtensions()
{
    uint32_t requiredExtensionCount;
    const char** requiredExtensions = glfwGetRequiredInstanceExtensions(&requiredExtensionCount);

    std::vector<const char*> extensions(requiredExtensions, requiredExtensions + requiredExtensionCount);
    if (ENABLE_VALIDATION_LAYERS)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extensions;
}

void VulkanInstance::SetupDebugMessenger()
{
    if (!ENABLE_VALIDATION_LAYERS)
        return;

    // ----- Debug messenger info -----
    VkDebugUtilsMessengerCreateInfoEXT messengerInfo;
    PopulateDebugMessengerInfo(&messengerInfo);

    // ----- Create Debug messenger -----
    auto vkCreateDebugUtilsMessengerEXT =
        Get_EXT_PFN<PFN_vkCreateDebugUtilsMessengerEXT>(&m_vkInstance, "vkCreateDebugUtilsMessengerEXT");
    if (vkCreateDebugUtilsMessengerEXT(m_vkInstance, &messengerInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)  // Function might not be loaded
    {
        assert(false && "Failed to create Debug messenger.");
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
) {
    // ----- Get severity of message -----
    std::string_view severity;
    switch (messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        severity = "DGN";  // Diagnostic
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        severity = "INF";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        severity = "WRN";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        severity = "ERR";
        assert(false);
        break;
    default:
        severity = "UNKNOWN MSG SEVERITY";
        assert(false && "UNKNOWN MSG SEVERITY");
        break;
    }

    // ----- Get type of message -----
    std::string_view msgType;
    switch (messageType)
    {
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
        msgType = "GENERAL";
        break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
        msgType = "VALIDATION";
        break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
        msgType = "PERFORMANCE";
        break;
    default:
        msgType = "UNKNOWN MSG TYPE";
        assert(false && "UNKNOWN MSG TYPE");
        break;
    }

    // ----- Get related object handles -----
    // for (uint32_t i = 0; i < pCallbackData->objectCount; i++)
    // {
    //     fmt::print("{}\n", pCallbackData->pObjects[i].objectHandle);
    // }

    fmt::print("[{} - {}] {}\n", severity, msgType, pCallbackData->pMessage);
    return VK_FALSE;
}

void VulkanInstance::PopulateDebugMessengerInfo(VkDebugUtilsMessengerCreateInfoEXT* dbg_messenger_info)
{
    dbg_messenger_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    dbg_messenger_info->pNext = nullptr;
    dbg_messenger_info->flags = 0;
    dbg_messenger_info->messageSeverity = 
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
        // | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    dbg_messenger_info->messageType = 
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    dbg_messenger_info->pfnUserCallback = debug_callback;
    dbg_messenger_info->pUserData = nullptr;  // Apparently optional
}

const VkInstance* VulkanInstance::GetVKInstance() const
{
    return &m_vkInstance;
}