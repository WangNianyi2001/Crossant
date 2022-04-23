#include "gdi.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

GDIContext::GDIContext(Window *window) : GraphicsContext(window) {
	window->legacy->UpdateInfo();
	bitmap = new Legacy::Bitmap(
		(Vector2U)window->legacy->info.clientRect.Diagonal()
	);
}

void GDIContext::Render() {
	Legacy::PaintStruct paintStruct;
	window->legacy->BeginPaint(&paintStruct);
	dc = paintStruct.GetDC();
	Push();
	window->legacy->EndPaint(&paintStruct);
}

void GDIContext::Resize(Vector2U size) {
}

void GDIContext::Pixel(Vector2F pos, Color3B color) {
	Legacy::ColorRef cr = RGB(color[0], color[1], color[2]);
	dc->SetPixel((int)pos[0], (int)pos[1], cr);
}
