
#include "BufferLayout.hpp"

namespace kyra {
	
	BufferLayout::iterator BufferLayout::begin() {
		return m_Elements.begin();
	}
		
	BufferLayout::iterator BufferLayout::end() {
		return m_Elements.end();
	}
		
	BufferLayout::const_iterator BufferLayout::begin() const {
		return m_Elements.begin();
	}
	
	BufferLayout::const_iterator BufferLayout::end() const {
		return m_Elements.end();
	}
		
	void BufferLayout::add(const std::string_view name, BufferElementType type, std::size_t count, std::size_t size, bool normalised) {
		BufferElement element;
		element.name = name;
		element.type = type;
		element.count = count;
		element.offset = m_Size;
		element.normalised = normalised;
		m_Size += size;
		m_Elements.emplace_back(element);
	}

	template<>
	void BufferLayout::add<uint32_t>(const std::string_view name, std::size_t count, bool normalised) {
		add(name, BufferElementType::UnsignedInt32, count, count * sizeof(uint32_t), normalised);
	}
	
	template<>
	void BufferLayout::add<uint8_t>(const std::string_view name, std::size_t count, bool normalised) {
		add(name, BufferElementType::UnsignedInt8, count, count * sizeof(uint8_t), normalised);
	}
	
	template<>
	void BufferLayout::add<float>(const std::string_view name, std::size_t count, bool normalised) {
		add(name, BufferElementType::Float, count, count * sizeof(float), normalised);
	}
	
}
