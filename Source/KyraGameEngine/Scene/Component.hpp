#ifndef KYRAGAMEENGINE_SCENE_COMPONENT_HPP
#define KYRAGAMEENGINE_SCENE_COMPONENT_HPP

namespace kyra {
 
  class Node;
  class Scene;
  class Component {

    Node* m_Node = nullptr;
    Scene* m_Scene = nullptr;

  public:
    virtual ~Component() = default;

    void setScene(Scene* scene) {
      m_Scene = scene;
    }
    
    Scene* getScene() const {
     return m_Scene; 
    }

    void setParent(Node* node) {
      m_Node = node;
    }

    Node* getNode() {
      return m_Node;
    }

    const Node* getNode() const {
      return m_Node;
    }

    virtual std::size_t getHash() const = 0;

  };
}

#endif