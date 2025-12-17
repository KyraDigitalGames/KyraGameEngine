#include "RenderPipeline.hpp"
#include "Renderer.hpp"
#include <KyraGameEngine/Debug/Profiling.hpp>


namespace kyra {
	
	bool RenderPipeline::init(RenderPipelineDescriptor& descriptor) {
		KYRA_PROFILE_FUNCTION();
		m_SystemManager = descriptor.systemManager;
		m_Renderer = descriptor.renderer;
		m_CommandBuffer = descriptor.renderer->acquireCommandBuffer();
		RenderPassDescriptor renderPassDescriptor;
		renderPassDescriptor.swapchain = descriptor.renderer->acquireSwapchain();
		renderPassDescriptor.processorRegistry = descriptor.renderPassProcessorRegistry;
		renderPassDescriptor.commandBuffer = m_CommandBuffer;
		renderPassDescriptor.systemManager = descriptor.systemManager;
		renderPassDescriptor.renderer = descriptor.renderer;
		for(auto& renderPasses : descriptor.m_RenderPasses) {
			renderPassDescriptor.processorNames.clear();
			renderPassDescriptor.processorNames.emplace_back(renderPasses.processorName);
			auto renderPass = descriptor.renderPassRegistry->create(renderPasses.name);
			if (!renderPass) {
				return false;
			}
			if(!renderPass->init(renderPassDescriptor)) {
				return false;
			}
			m_RenderPasses.emplace_back(renderPass);
		}
		return true;
	}

	void RenderPipeline::renderFrame() {
		KYRA_PROFILE_FUNCTION();
		for (auto& renderPass : m_RenderPasses) {
			renderPass->renderFrame(m_CommandBuffer);
		}
	}

}