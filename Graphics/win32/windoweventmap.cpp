#include "window.hpp"
#include <Windows.h>

using Graphics::WindowEventType;

std::map<unsigned, WindowEventType> Graphics::Win32::Window::eventMap = std::map<unsigned, WindowEventType>{
	{ WM_CLOSE, WindowEventType::Close }
};
