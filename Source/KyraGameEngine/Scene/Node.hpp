#ifndef KYRAGAMEENGINE_SCENE_NODE_HPP
#define KYRAGAMEENGINE_SCENE_NODE_HPP

#include <KyraGameEngine/Serializing/Serializable.hpp>
#include "Component.hpp"
#include <map>
#include <vector>
#include <string>

namespace kyra {
 
class Scene;
class Node : public Serializable {

  std::string m_Name = "";

	std::map<std::size_t, Component*> m_Components;

	Node* m_Parent = nullptr;
	std::vector<Node*> m_Children;
  
  Scene* m_Scene = nullptr;

public:

  void setScene(Scene* scene) {
    m_Scene = scene;
  }
  
  Scene* getScene() const {
    return m_Scene;
  }

	std::vector<Node*>& getChildren() {
		return m_Children;
	}
  
  void setName(const std::string& name) {
    m_Name = name;
  }
  
  const std::string& getName() const {
    return m_Name;
  }

	const std::vector<Node*>& getChildren() const {
		return m_Children;
	}

	void addComponent(Component* component) {
		auto id = component->getHash();
		component->setParent(this);
    component->setScene(m_Scene);
		m_Components.emplace(id, component);
	}

	template<class ComponentType>
	bool hasComponent() const {
		auto id = typeid(ComponentType).hash_code();
		auto it = m_Components.find(id);
		return it != m_Components.end();
	}

	template<class ComponentType>
	ComponentType* getComponent() {
		auto id = typeid(ComponentType).hash_code();
		auto it = m_Components.find(id);
		if(it != m_Components.end()) {
			return static_cast<ComponentType*>(it->second);
		}
		return nullptr;
	}

	template<class ComponentType>
	const ComponentType* getComponent() const {
		auto id = typeid(ComponentType).hash_code();
		auto it = m_Components.find(id);
		if (it != m_Components.end()) {
			return static_cast<ComponentType*>(it->second);
		}
		return nullptr;
	}

	void setParent(Node* node) {
		m_Parent = node;
	}

	Node* getParent() noexcept {
		return m_Parent;
	}

	const Node* getParent() const noexcept {
		return m_Parent;
	}

  void write(BinaryWriter& writer) {
    writer.write(m_Name);
    writer.write(m_Components.size());
    for(auto& component : m_Components) {
      //component.second->write(writer);
    }
  }


};
 
}

#endif