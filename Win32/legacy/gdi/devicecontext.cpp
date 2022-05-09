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
	RectRange const &clip,
	Coord2D const &offset
) {
	Coord2D diag = clip.Diagonal();
	BitBlt(
		dest->GetHandle<HDC>(),
		(int)clip.min[0], (int)clip.min[1],
		(int)diag[0], (int)diag[1],
		GetHandle<HDC>(),
		(int)offset[0], (int)offset[1],
		SRCCOPY
	);
}

void DeviceContext::Select(GDIObject *object) {
	SelectObject(GetHandle<HDC>(), object->GetHandle<HGDIOBJ>());
}

void DeviceContext::SetPixel(int x, int y, ColorRef color) {
	::SetPixel(GetHandle<HDC>(), x, y, color.value);
}

void DeviceContext::Rectangle(int left, int top, int right, int bottom) {
	::Rectangle(GetHandle<HDC>(), left, top, right, bottom);
}
