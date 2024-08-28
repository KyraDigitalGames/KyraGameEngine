#ifndef KYRAGAMEENGINE_RHI_BUFFERLAYOUT_HPP
#define KYRAGAMEENGINE_RHI_BUFFERLAYOUT_HPP

#include <string_view>
#include <vector>
#include <cstdint>

namespace kyra {
	
	enum class BufferElementType {
		Float,
		UnsignedInt32,
		UnsignedInt8
	};
	
	struct BufferElement {
		std::string_view name;
		BufferElementType type = BufferElementType::Float;
		uint32_t count  = 0;
		std::size_t offset = 0;
		bool normalised = false;
	};
	
	class BufferLayout {
		
		std::vector<BufferElement> m_Elements;
		std::size_t m_Size = 0;
		
		public:
		
		using iterator = std::vector<BufferElement>::iterator;
		[[nodiscard]] iterator begin();
		[[nodiscard]] iterator end();
		
		using const_iterator = std::vector<BufferElement>::const_iterator;
		[[nodiscard]] const_iterator begin() const;
		[[nodiscard]] const_iterator end() const;
		
		
		void add(const std::string_view name, BufferElementType type, std::size_t count, std::size_t size, bool normalised);

		template<class T>
		void add(const std::string_view name, std::size_t count, bool normalised = false);
		
		[[nodiscard]] constexpr std::size_t getSize() const {
			return m_Size;
		}
	};
	
	
	template<>
	void BufferLayout::add<uint32_t>(const std::string_view name, std::size_t count, bool normalised);
	
	template<>
	void BufferLayout::add<uint8_t>(const std::string_view name, std::size_t count, bool normalised);
	
	template<>
	void BufferLayout::add<float>(const std::string_view name, std::size_t count, bool normalised);
	


	
}

#endif