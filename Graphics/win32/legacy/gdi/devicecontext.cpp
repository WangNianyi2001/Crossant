#include "devicecontext.hpp"
#include <Windows.h>

using namespace Graphics::Win32::Legacy;

DeviceContext *PaintStruct::GetDC() {
	return new DeviceContext(((LPPAINTSTRUCT)ps)->hdc);
}

DeviceContext::~DeviceContext() {
	DeleteDC(GetHandle<HDC>());
}

void DeviceContext::Select(GDIObject *object) {
	SelectObject(GetHandle<HDC>(), object->GetHandle<HGDIOBJ>());
}

void DeviceContext::SetPixel(int x, int y, Color::Hex color) {
	::SetPixel(GetHandle<HDC>(), x, y, color);
}
