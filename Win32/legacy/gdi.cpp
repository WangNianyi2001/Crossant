#include "gdi.hpp"
#include <Windows.h>

using namespace Graphics::Legacy;

PaintStruct::PaintStruct() : ps(new PAINTSTRUCT) {}

PaintStruct::~PaintStruct() {
	delete ps;
}

