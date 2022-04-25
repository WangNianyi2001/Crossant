#include "pen.hpp"
#include <Windows.h>

using namespace Graphics::Legacy;

CosmeticPen::CosmeticPen(int width, ColorRef color)
	: Pen(CreatePen(PS_SOLID, width, color.value)) {
}
