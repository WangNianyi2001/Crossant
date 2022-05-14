#pragma once

#include "Crossant/feature/keyboard.hpp"
#include <map>
#include <Windows.h>

namespace Crossant {
	using Key = Keyboard::Key;

	Byte KeyToVK(Key key);

	Key VKToKey(Byte vk);

	constexpr SHORT mask = 1U << ((sizeof(SHORT) << 3) - 1);
}