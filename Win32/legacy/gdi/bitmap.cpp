#include "bitmap.hpp"
#include <Windows.h>

using namespace Graphics::Legacy;

HBITMAP CreateBitmap(Graphics::Size2D size) {
	BITMAPINFOHEADER header{
		.biSize = sizeof(BITMAPINFOHEADER),
		.biWidth = (long)size[0],
		.biHeight = -(long)size[1],
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
	HBITMAP hBm = CreateDIBSection(
		NULL,
		&info,
		DIB_RGB_COLORS,
		&out,
		NULL, 0
	);
	if(hBm == NULL)
		TryThrowLastError();
	return hBm;
}

inline HBITMAP CreateBitmap(DeviceContext &dc) {
	return (HBITMAP)GetCurrentObject(dc.GetHandle<HDC>(), OBJ_BITMAP);
}

Bitmap::Bitmap(Size2D size) :
	GDIObject(CreateBitmap(size)),
	size(size), dc(*new DeviceContext(CreateCompatibleDC(NULL))) {
	dc.Select(this);
}

Bitmap::Bitmap(DeviceContext &dc, Size2D size) :
	GDIObject(CreateBitmap(dc)),
	size(size),
	dc(dc) {
}

Bitmap::~Bitmap() {
	DeleteObject(GetHandle<HBITMAP>());
	delete &dc;
}
