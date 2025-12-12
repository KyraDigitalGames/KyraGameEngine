#ifndef KYRAGAMEENGINE_RENDERER_RENDERPASSPROCESSOR_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERPASSPROCESSOR_HPP


#include <KyraGameEngine/Core/SystemManager.hpp>

namespace kyra {

	class Renderer;
	class CommandBuffer;
	class RenderPassProcessor {

		SystemManager* m_SystemManager;
		

	public:
		virtual ~RenderPassProcessor() = default;

		void setSystemManager(SystemManager* systemManager) {
			m_SystemManager = systemManager;
		}

		template<class SystemType> SystemType* getSystem() {
			return m_SystemManager->getSystem<SystemType>();
		}

		virtual bool init(Renderer& renderer) = 0;
		virtual void update(CommandBuffer* commandBuffer) = 0;

	};

}

#endif