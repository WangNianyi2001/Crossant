#include "devicecontext.hpp"
#include <Windows.h>

using namespace Graphics::Legacy;

DeviceContext *PaintStruct::GetDC() {
	return new DeviceContext(((LPPAINTSTRUCT)ps)->hdc, false);
}

DeviceContext::~DeviceContext() {
	if(isPrivate)
		DeleteDC(GetHandle<HDC>());
}

void DeviceContext::PutTo(
	DeviceContext *dest,
	ScreenRect const &clip,
	ScreenCoord const &offset
) {
	ScreenCoord diag = clip.Diagonal();
	BitBlt(
		dest->GetHandle<HDC>(),
		clip.min[0], clip.min[1],
		diag[0], diag[1],
		GetHandle<HDC>(),
		offset[0], offset[1],
		SRCCOPY
	);
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
