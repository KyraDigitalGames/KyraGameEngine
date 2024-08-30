
#include <windows.h>
#include <KyraGameEngine/Platform/MessageBox.hpp>

namespace kyra {
	
	void MessageBox::showInfo(const std::string_view title, const std::string_view message) 
	{
		MessageBoxA(NULL, message.data(), title.data(), MB_OK);
	}
	
	void MessageBox::showError(const std::string_view title, const std::string_view message) 
	{
		MessageBoxA(NULL, message.data(), title.data(), MB_OK);		
	}
		
}