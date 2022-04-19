#include "gdi.hpp"
#include <Windows.h>
#pragma comment(lib, "Msimg32.lib")

using namespace Graphics::Win32;

void GDIContext::Line() {
	auto &ps = *(PAINTSTRUCT *)window->paintStruct;
	MoveToEx(ps.hdc, 0, 0, NULL);
	LineTo(ps.hdc, 100, 100);
	StrokePath(ps.hdc);
}
