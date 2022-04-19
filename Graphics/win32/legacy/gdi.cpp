#include "gdi.hpp"
#include <Windows.h>

using namespace Graphics::Win32::Legacy;

PaintStruct::PaintStruct() :ps(new PAINTSTRUCT) {}

PaintStruct::~PaintStruct() {
	delete ps;
}

DeviceContext *PaintStruct::GetDC() {
	return new DeviceContext(((LPPAINTSTRUCT)ps)->hdc);
}

void DeviceContext::Destroy() {
	DeleteDC(GetHandle<HDC>());
}

void DeviceContext::SetPixel(int x, int y, ColorRef color) {
	::SetPixel(GetHandle<HDC>(), x, y, color);
}
