#ifndef KYRAGAMEENGINE_RENDERER_RENDERDEVICEIMPLEMENTATIONVULKAN_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERDEVICEIMPLEMENTATIONVULKANL_HPP

#include <vulkan/vulkan.h>

#include <KyraGameEngine/Renderer/RenderDeviceImplementation.hpp>
#include "SwapchainVulkan.hpp"
#include "CommandBufferVulkan.hpp"

#include <vector>
#include <map>

namespace kyra {

	class RenderDeviceImplementationVulkan : public RenderDeviceImplementation {

		VkInstance m_Instance;

		SwapchainVulkan m_Swapchain;
		CommandBufferVulkan m_CommandBuffer;

		bool isDeviceSuitable(VkPhysicalDevice device) const;
		VkPhysicalDevice getBestPhysicalDevice(std::vector<VkPhysicalDevice>& devices) const;
		int rateDeviceSuitability(const VkPhysicalDevice& renderDevice) const;
		uint32_t findQueueFamilies(VkPhysicalDevice device) const;

	public:
		virtual ~RenderDeviceImplementationVulkan();
		
		bool init(RenderDeviceDescriptor& renderDeviceDescriptor) final;
		Swapchain* acquireSwapchain() final;
		CommandBuffer* acquireCommandBuffer() final;

	};

}

#endif