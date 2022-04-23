#include "gdi.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

GDIContext::GDIContext(Window *window) : GraphicsContext(window) {
	window->legacy->UpdateInfo();
	bitmap = new Legacy::Bitmap(
		(Vector2U)window->legacy->info.clientRect.Diagonal()
	);
	Configure([this]() {
		Legacy::PaintStruct paintStruct;
		this->window->legacy->BeginPaint(&paintStruct);
		BitBlt(
			paintStruct.GetDC()->GetHandle<HDC>(),
			0, 0,
			this->bitmap->size[0], bitmap->size[1],
			this->bitmap->dc->GetHandle<HDC>(),
			0, 0,
			SRCCOPY
		);
		this->window->legacy->EndPaint(&paintStruct);
	});
}

GDIContext::~GDIContext() {
	delete bitmap;
}

void GDIContext::Resize(Vector2U size) {
}

void GDIContext::Pixel(Vector2F pos, Color3B color) {
	Legacy::ColorRef cr = RGB(color[0], color[1], color[2]);
	bitmap->dc->SetPixel((int)pos[0], (int)pos[1], cr);
}
