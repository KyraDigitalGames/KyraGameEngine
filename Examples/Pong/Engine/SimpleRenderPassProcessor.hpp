#ifndef PONG_SIMPLERENDERPASSPROCESSOR_HPP
#define PONG_SIMPLERENDERPASSPROCESSOR_HPP

#include <KyraGameEngine/Renderer/RenderPassProcessor.hpp>

class SimpleRenderPassProcessor : kyra::RenderPassProcessor {

public:

	bool init(kyra::Renderer& renderer) {
		return true;
	}

	void update(kyra::CommandBuffer* commandBuffer) {

	}

};

#endif