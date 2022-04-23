#include "gdi.hpp"
#include <Windows.h>

using namespace Graphics::Win32::Legacy;

PaintStruct::PaintStruct() : ps(new PAINTSTRUCT) {}

PaintStruct::~PaintStruct() {
	delete ps;
}

