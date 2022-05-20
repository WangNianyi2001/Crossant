#pragma once

#include "Crossant/common/basic.hpp"
#include <Windows.h>

namespace Crossant {
	COLORREF ColorToChannel(Color color, unsigned i);

	COLORREF ColorToRef(Color color);

	void TryThrowLastError();
}