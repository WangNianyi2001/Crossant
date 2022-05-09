#include "bitmap.hpp"
#include <Windows.h>

using namespace Graphics::Legacy;

HBITMAP CreateBitmap(Graphics::Vector2U size) {
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

HBITMAP CreateBitmap(DeviceContext &dc) {
	BITMAP bm;
	memset(&bm, 0, sizeof(BITMAP));
	HBITMAP hBm = (HBITMAP)GetCurrentObject(dc.GetHandle<HDC>(), OBJ_BITMAP);
	return hBm;
}

Graphics::Vector2U GetBmSize(HBITMAP hBm) {
	BITMAP bm;
	memset(&bm, 0, sizeof(BITMAP));
	GetObject(hBm, sizeof(BITMAP), &bm);
	return { (unsigned)bm.bmWidth, (unsigned)bm.bmHeight };
}

Bitmap::Bitmap(Vector2U size) :
	GDIObject(CreateBitmap(size)),
	size(size), dc(*new DeviceContext(CreateCompatibleDC(NULL))) {
	dc.Select(this);
}

Bitmap::Bitmap(DeviceContext &dc) :
	GDIObject(CreateBitmap(dc)),
	size(GetBmSize(GetHandle<HBITMAP>())),
	dc(dc) {
}

Bitmap::~Bitmap() {
	DeleteObject(GetHandle<HBITMAP>());
	delete &dc;
}
