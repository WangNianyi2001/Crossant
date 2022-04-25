#pragma once

#include "brush.hpp"
#include <Windows.h>

using namespace Graphics::Legacy;

SolidBrush::SolidBrush(ColorRef color) :
	Brush(CreateSolidBrush(color.value)) {}

SolidBrush::~SolidBrush() {
	DeleteObject(GetHandle<HBRUSH>());
}
