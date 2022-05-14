#include "Crossant/feature/mouse.hpp"
#include <map>
#include <Windows.h>

using namespace Crossant;

using MB = Mouse::Button;

int ButtonToVK(MB button) {
	switch(button) {
	case MB::Left:
		return VK_LBUTTON;
	case MB::Middle:
		return VK_MBUTTON;
	case MB::Right:
		return VK_RBUTTON;
	default:
		return 0;
	}
}

constexpr SHORT mask = 1U << ((sizeof(SHORT) << 3) - 1);

bool Mouse::Pressed(MB button) {
	return GetAsyncKeyState(ButtonToVK(button)) & mask;
}