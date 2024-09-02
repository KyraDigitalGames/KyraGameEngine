#ifndef KYRAGAMEENGINE_RHI_DESCRIPTORSET_HPP
#define KYRAGAMEENGINE_RHI_DESCRIPTORSET_HPP

#include <vector>
#include "AbstractPipeline.hpp"

namespace kyra {
	
	struct DescriptorSetLayoutEntry {
		std::string_view id = "";
		std::size_t type = 0;
		std::size_t size = 0;
		std::size_t offset = 0;
	};
	
	struct DescriptorSetLayout {
		std::vector<DescriptorSetLayoutEntry> entries;
		std::size_t size = 0;
		void* data = nullptr;
	};
	
	class DescriptorSet {
		
		DescriptorSetLayout* m_Layout = nullptr;
		
		void* getDataPtr(const std::string_view id) {
			if(m_Layout) {
				for(auto& entry : m_Layout->entries) {
					if(entry.id == id) {
						return m_Layout->data + entry.offset;
					}
				}
			}
			return nullptr;
		}
		
		public:
		
		void setValue(std::string_view id, std::size_t size, void* data) {
			void* target = getDataPtr(id);
			if(target) {
				memcpy(target, data, size);
			}
		}
		
		template<class T>
		T* getValue(std::string_view id) {
			void* target = getDataPtr(id);
			if(target) {
				return reinterpret_cast<T*>(target);
			}
			return nullptr;
		}
		
		const DescriptorSetLayout* getLayout() const {
			return m_Layout;
		}
		
		
	};
}

#endif