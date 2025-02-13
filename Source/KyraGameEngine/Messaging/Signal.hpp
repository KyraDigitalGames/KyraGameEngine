#ifndef KYRAGAMEENGINE_MESSAGING_SIGNAL_HPP
#define KYRAGAMEENGINE_MESSAGING_SIGNAL_HPP

#include <unordered_map>
#include <functional>

namespace kyra {
  
  template<typename FunctionDefintion>
  class Signal {
    
    std::unordered_map<std::size_t, std::function<FunctionDefintion>> m_FunctionMap;
    
    public:
    
    void connect(void* owner, std::function<FunctionDefintion> function) {
      m_FunctionMap[reinterpret_cast<std::size_t>(owner)] = function;
    }
    
    void disconnect(void* owner) {
      auto it = m_FunctionMap.find(reinterpret_cast<std::size_t>(owner));
      if(it != m_FunctionMap.end()) {
        m_FunctionMap.erase(it);
      }
    }
    
    template<class ... Args>
    void dispatch(Args... args) {
      for(auto& entry : m_FunctionMap) {
        entry.second(args...);
      }
    }
        
  };
  
}

#endif