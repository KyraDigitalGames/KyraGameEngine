#ifndef KYRAGAMEENGINE_GAMEMODULE_GAMEMODULE_HPP
#define KYRAGAMEENGINE_GAMEMODULE_GAMEMODULE_HPP

#include <KyraGameEngine/Scripting/Actor.hpp>
#include <KyraGameEngine/Renderer/RenderPassProcessor.hpp>
#include "ActorRegistry.hpp"
#include "RenderPassProcessorRegistry.hpp"
#include <Windows.h>
#include <string>
#include <iostream>
#include <map>

namespace kyra {

	template<class BaseType>
	class FactoryInterface {

	public:

		virtual std::shared_ptr<BaseType> create() = 0;

	};


	template<class BaseType, class ImplementationType>
	class Factory : public FactoryInterface<BaseType> {

	public:

		std::shared_ptr<BaseType> create() final {
			return std::make_shared<ImplementationType>();
		}

	};

	template<class BaseClass>
	class Registry {

		std::map<std::string, std::unique_ptr<FactoryInterface<BaseClass>>> m_Factories;


	public:

		template<class ImplementationType>
		void registerFactory(const std::string& name) {
			m_Factories[name] = std::make_unique<Factory<BaseClass, ImplementationType>>();
		}

		std::shared_ptr<BaseClass> create(const std::string& name) {
			auto it = m_Factories.find(name);
			if (it == m_Factories.end()) {
				return nullptr;
			}
			return it->second->create();
		}

	};
	
	struct GameModuleContext {
		Registry<Actor> actorRegistry;
		Registry<RenderPassProcessor> renderPassProcessorRegistry;
	};

	typedef bool (*KYRA_REGISTRATION_PROC)(GameModuleContext& context);

	class GameModule {

		HMODULE m_Handle = NULL;
		std::unique_ptr<GameModuleContext> m_Context;

	public:
		~GameModule() {
			m_Context.reset();
			if (m_Handle) {
				FreeLibrary(m_Handle);
			}
		}

		bool load(const std::string& file) {
			m_Context = std::make_unique<GameModuleContext>();
			m_Handle = LoadLibraryA(file.c_str());
			if (!m_Handle) {
				return false;
			}
			KYRA_REGISTRATION_PROC registrationFunc;
			registrationFunc = (KYRA_REGISTRATION_PROC)(GetProcAddress(m_Handle, "kyra_internal_register_game_module"));
			if (!registrationFunc) {
				std::cout << "kyra_internal_register_game_module was not found in game.dll" << std::endl;
				return false;
			}
			registrationFunc((*m_Context.get()));
			return (m_Handle != NULL);
		}

		std::shared_ptr<Actor> createActor(const std::string& id) {
			return m_Context->actorRegistry.create(id);
		}

	};

}

#define KYRA_GAMEMODULE_START(GameModuleName) extern "C" { bool __declspec(dllexport)  kyra_internal_register_game_module(kyra::GameModuleContext& context) {
#define KYRA_REGISTER_ACTOR(ActorType) context.actorRegistry.registerFactory<ActorType>(#ActorType);
#define KYRA_REGISTER_RENDERPASSPROCESSOR(RenderPassProcessorType) //context.renderPassProcessorRegistry.registerFactory<RenderPassProcessorType>(#RenderPassProcessorType);
#define KYRA_GAMEMMODULE_END return true;} }

#endif