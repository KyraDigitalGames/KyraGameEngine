#ifndef KYRAGAMEENGINE_RENDERER_RENDERPASSPROCESSOR_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERPASSPROCESSOR_HPP


namespace kyra {

	class Renderer;
	class CommandBuffer;
	class RenderPassProcessor {

	public:
		virtual ~RenderPassProcessor() = default;

		virtual bool init(Renderer& renderer) = 0;
		virtual void update(CommandBuffer* commandBuffer) = 0;

	};

}

#endif