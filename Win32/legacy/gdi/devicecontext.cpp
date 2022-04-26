#include "devicecontext.hpp"
#include <Windows.h>

using namespace Graphics::Legacy;

DeviceContext *PaintStruct::GetDC() {
	return new DeviceContext(((LPPAINTSTRUCT)ps)->hdc);
}

DeviceContext::~DeviceContext() {
	DeleteDC(GetHandle<HDC>());
}

void DeviceContext::Select(GDIObject *object) {
	SelectObject(GetHandle<HDC>(), object->GetHandle<HGDIOBJ>());
}

void DeviceContext::SetPixel(int x, int y, ColorRef color) {
	::SetPixel(GetHandle<HDC>(), x, y, color.value);
}

void DeviceContext::Rect(int left, int top, int right, int bottom) {
	Rectangle(GetHandle<HDC>(), left, top, right, bottom);
}
