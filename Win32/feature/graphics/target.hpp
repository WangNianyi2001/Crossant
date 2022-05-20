#pragma once

#include "Crossant/feature/graphics/target.hpp"
#include "Win32/legacy.hpp"
#include <Windows.h>

namespace Crossant::Graphics {
	struct Target::Impl {
		Size2D size;
		HBITMAP hBm;
		HDC hDC;
		bool isFree = true;

		Impl(Size2D size);
		Impl(HDC hDC, Size2D size);

		~Impl();
	};
}
