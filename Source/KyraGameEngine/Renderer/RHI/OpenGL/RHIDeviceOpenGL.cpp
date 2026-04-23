#include "RHIDeviceOpenGL.hpp"

namespace kyra {
	
	RHIDevice::Ptr RHIDevice::create() {
		return std::make_unique<RHIDeviceOpenGL>();
	}

}