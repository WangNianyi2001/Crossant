#include "bitmap.hpp"
#include <Windows.h>

using namespace Graphics::Win32::Legacy;

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

Bitmap::Bitmap(Vector2U size) :
	GDIObject(CreateBitmap(size)),
	size(size), dc(new DeviceContext(CreateCompatibleDC(NULL))) {
	dc->Select(this);
}

Bitmap::~Bitmap() {
	DeleteObject(GetHandle<HBITMAP>());
	dc->Destroy();
}
