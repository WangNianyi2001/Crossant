#include "target.hpp"
#include "Crossant/feature/graphics/context.hpp"
#include <Windows.h>

using namespace Crossant::Graphics;

Target::Impl::Impl(Size2D size) : size(size) {
	BITMAPINFOHEADER header{
		.biSize = sizeof(BITMAPINFOHEADER),
		.biWidth = (long)size[0],
		.biHeight = (long)size[1],
		.biPlanes = 1,
		.biBitCount = 32,
		.biCompression = BI_RGB,
		.biSizeImage = 0,
		.biXPelsPerMeter = 1,	// Invalid
		.biYPelsPerMeter = 1,	// Invalid
		.biClrUsed = 0,
		.biClrImportant = 0
	};
	BITMAPINFO info{
		.bmiHeader = header,
		.bmiColors = { RGBQUAD{ 0, 0, 0, 0 } }
	};
	void *out;
	hBm = CreateDIBSection(
		NULL,
		&info,
		DIB_RGB_COLORS,
		&out,
		NULL, 0
	);
	if(hBm == NULL)
		throw GetLastError();
	hDC = CreateCompatibleDC(NULL);
	SelectObject(hDC, hBm);
}

Target::Impl::Impl(HDC hDC, Size2D size) : isFree(false), hDC(hDC), size(size) {
	hBm = (HBITMAP)GetCurrentObject(hDC, OBJ_BITMAP);
}

Target::Impl::~Impl() {
	if(isFree) {
		DeleteObject(hBm);
		DeleteDC(hDC);
	}
}

Target::Target(Impl *impl) : impl(impl) {}
Target::Target(Size2D size) : impl(new Impl(size)) {}

Target::~Target() {
	delete impl;
}

Crossant::Size2D Target::Size() const {
	return impl->size;
}

void Target::Resize(Size2D size) {
 	delete impl;
	impl = new Impl(size);
	for(auto context : contexts)
		context->OnResize();
}

void Target::DrawOn(Target &target) {
	BitBlt(
		target.impl->hDC, 0, 0, target.impl->size[0], target.impl->size[1],
		impl->hDC, impl->size[0], impl->size[1], SRCCOPY
	);
}
