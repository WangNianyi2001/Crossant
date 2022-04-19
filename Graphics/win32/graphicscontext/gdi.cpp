#include "gdi.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

void GDIContext::Begin() {
	window->legacy->BeginPaint(&paintStruct);
	dc = paintStruct.GetDC();
}

void GDIContext::End() {
	window->legacy->EndPaint(&paintStruct);
}

void GDIContext::Pixel(Point2F pos, Color3B color) {
	Legacy::ColorRef cr = RGB(color[0], color[1], color[2]);
	dc->SetPixel((int)pos[0], (int)pos[1], cr);
}
