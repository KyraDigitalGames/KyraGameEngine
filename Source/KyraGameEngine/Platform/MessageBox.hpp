#ifndef KYRAGAMEENGINE_PLATFORM_MESSAGEBOX_HPP
#define KYRAGAMEENGINE_PLATFORM_MESSAGEBOX_HPP

#include <string_view>

#ifdef MessageBox
	#undef MessageBox
#endif

namespace kyra {
	
	class MessageBox {
		
		public:
		
		static void showInfo(const std::string_view title, const std::string_view message);
		static void showError(const std::string_view title, const std::string_view message);
				
	};
	
}

#endif