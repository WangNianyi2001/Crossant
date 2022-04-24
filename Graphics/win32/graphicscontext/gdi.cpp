#include "gdi.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

GDIContext::GDIContext(Window *window) : window(window) {
	Resize((Vector2U)window->ClientRect().Diagonal());
	Configure([this]() {
		Legacy::PaintStruct paintStruct;
		this->window->legacy->BeginPaint(&paintStruct);
		Legacy::DeviceContext *targetDC = paintStruct.GetDC();
		BitBlt(
			targetDC->GetHandle<HDC>(),
			0, 0,
			this->bitmap->size[0], bitmap->size[1],
			this->bitmap->dc->GetHandle<HDC>(),
			0, 0,
			SRCCOPY
		);
		delete targetDC;
		this->window->legacy->EndPaint(&paintStruct);
	});
}

GDIContext::~GDIContext() {
	if(bitmap != nullptr)
		delete bitmap;
	bitmap = nullptr;
}

void GDIContext::Resize(Vector2U size) {
	if(bitmap != nullptr)
		delete bitmap;
	bitmap = new Legacy::Bitmap(size);
}

void GDIContext::Pixel(Vector2F pos, Color color) {
	bitmap->dc->SetPixel((int)pos[0], (int)pos[1], Legacy::ColorRef(color));
}
