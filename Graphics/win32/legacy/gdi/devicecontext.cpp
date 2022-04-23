#include "devicecontext.hpp"
#include <Windows.h>

using namespace Graphics::Win32::Legacy;

DeviceContext *PaintStruct::GetDC() {
	return new DeviceContext(((LPPAINTSTRUCT)ps)->hdc);
}

void DeviceContext::Destroy() {
	DeleteDC(GetHandle<HDC>());
}

void DeviceContext::Select(GDIObject *object) {
	SelectObject(GetHandle<HDC>(), object->GetHandle<HGDIOBJ>());
}

void DeviceContext::SetPixel(int x, int y, ColorRef color) {
	::SetPixel(GetHandle<HDC>(), x, y, color);
}
