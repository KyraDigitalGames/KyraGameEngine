#ifndef KYRAGAMEENGINE_SCENE_COMPONENT_HPP
#define KYRAGAMEENGINE_SCENE_COMPONENT_HPP

#include <KyraGameEngine/Serializing/Serializable.hpp>

namespace kyra {
 
  class Node;
  class Component : public Serializable {

    Node* m_Node = nullptr;

  public:
    virtual ~Component() = default;

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

    void write(BinaryWriter& writer) override {

    }

  };
}

#endif