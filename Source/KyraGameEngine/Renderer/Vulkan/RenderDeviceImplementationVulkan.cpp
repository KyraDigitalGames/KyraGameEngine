#include "RenderDeviceImplementationVulkan.hpp"
#include <KyraGameEngine/Log/Logger.hpp>
#include <vector>

namespace kyra {


	RenderDeviceImplementationVulkan::~RenderDeviceImplementationVulkan() {
		vkDestroyInstance(m_Instance, nullptr);
	}

	int RenderDeviceImplementationVulkan::rateDeviceSuitability(const VkPhysicalDevice& renderDevice) const {
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(renderDevice, &deviceProperties);
		vkGetPhysicalDeviceFeatures(renderDevice, &deviceFeatures);
		int score = 0;
		// Discrete GPUs have a significant performance advantage
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			score += 1000;
		}
		// Maximum possible size of textures affects graphics quality
		score += deviceProperties.limits.maxImageDimension2D;
		
		KYRA_LOG_INFO(deviceProperties.deviceName << " " << deviceProperties.driverVersion << " " << score);
		
		// Application can't function without geometry shaders
		if (!deviceFeatures.geometryShader) {
			return 0;
		}
		return 0;
	}

	bool RenderDeviceImplementationVulkan::isDeviceSuitable(VkPhysicalDevice device) const {
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
		return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;
	}


	VkPhysicalDevice RenderDeviceImplementationVulkan::getBestPhysicalDevice(std::vector<VkPhysicalDevice>& devices) const {
		std::multimap<int, VkPhysicalDevice> candidates;
		for (const auto& device : devices) {
			int score = rateDeviceSuitability(device);
			candidates.insert(std::make_pair(score, device));
		}
		// Check if the best candidate is suitable at all
		if (candidates.rbegin()->first > 0) {
			return candidates.rbegin()->second;
		}
		return 0;
	}

	uint32_t RenderDeviceImplementationVulkan::findQueueFamilies(VkPhysicalDevice device) const {
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				return i;
			}
			i++;
		}
		return 0;
	}


	// Use an ordered map to automatically sort candidates by increasing score

	bool RenderDeviceImplementationVulkan::init(RenderDeviceDescriptor& renderDeviceDescriptor) {
		
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Kyra Game Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Kyra Game Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Get avaulable extensions

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		KYRA_LOG_INFO("Available Vulkan extensions: ");
		std::vector<const char*> activeExtensions(extensions.size());
		
		int id = 0;
		for (auto& entry : extensions) {
			KYRA_LOG_INFO(entry.extensionName << " " << entry.specVersion);
			activeExtensions[id] = entry.extensionName;
			id++;
		}

		// Get available layers

		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		std::vector<const char*> activeLayers(availableLayers.size());

		id = 0;
		KYRA_LOG_INFO("Available Vulkan layers: ");
		for (auto& entry : availableLayers) {
			KYRA_LOG_INFO(entry.layerName << " " << entry.specVersion);
			activeLayers[id] = entry.layerName;
			id++;
		}


		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = extensions.size();
		createInfo.ppEnabledExtensionNames = &activeExtensions[0];
		createInfo.enabledLayerCount = layerCount;
		createInfo.ppEnabledLayerNames = &activeLayers[0];

		int result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
		if ( result != VK_SUCCESS) {
			KYRA_LOG_ERROR("Failed to create vulkan instance ( " << result << " )");
			if (result == VK_ERROR_EXTENSION_NOT_PRESENT) {
				KYRA_LOG_ERROR("VK_ERROR_EXTENSION_NOT_PRESENT");
			}
			else if (result == VK_ERROR_INCOMPATIBLE_DRIVER) {
				KYRA_LOG_ERROR("VK_ERROR_INCOMPATIBLE_DRIVER");
			}
			else if (result == VK_ERROR_INITIALIZATION_FAILED) {
				KYRA_LOG_ERROR("VK_ERROR_INITIALIZATION_FAILED");
			}
			else if (result == VK_ERROR_LAYER_NOT_PRESENT) {
				KYRA_LOG_ERROR("VK_ERROR_LAYER_NOT_PRESENT");
			}
			else if (result == VK_ERROR_OUT_OF_DEVICE_MEMORY) {
				KYRA_LOG_ERROR("VK_ERROR_OUT_OF_DEVICE_MEMORY");
			}
			else if (result == VK_ERROR_OUT_OF_HOST_MEMORY) {
				KYRA_LOG_ERROR("VK_ERROR_OUT_OF_HOST_MEMORY");
			}
			else if (result == VK_ERROR_UNKNOWN) {
				KYRA_LOG_ERROR("VK_ERROR_UNKNOWN");
			}
			return false;
		}

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			KYRA_LOG_ERROR("Failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());
		for (const auto& device : devices) {
			if (isDeviceSuitable(device)) {
				physicalDevice = device;
				break;
			}
		}

		if (physicalDevice == VK_NULL_HANDLE) {
			KYRA_LOG_ERROR("failed to find a suitable GPU!");
		}

		VkPhysicalDevice bestDevice = getBestPhysicalDevice(devices);

		SwapchainDescriptor swapchainDescriptor;
		swapchainDescriptor.window = renderDeviceDescriptor.window;
		return m_Swapchain.init(swapchainDescriptor);
	}

	Swapchain* RenderDeviceImplementationVulkan::acquireSwapchain() {
		return &m_Swapchain;
	}


	CommandBuffer* RenderDeviceImplementationVulkan::acquireCommandBuffer() {
		return &m_CommandBuffer;
	}

}