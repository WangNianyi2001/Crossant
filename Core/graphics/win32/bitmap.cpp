#include "bitmap.hpp"

using namespace Graphics::Win32;

BLENDFUNCTION BitmapContext::blend_function = {
	AC_SRC_OVER, 0, 255, AC_SRC_ALPHA
};

void BitmapContext::Dispose() {
	if(data != nullptr) {
		delete[] data;
		data = nullptr;
	}
	if(hBm != NULL) {
		DeleteObject(hBm);
		hBm = NULL;
	}
}

BitmapContext::~BitmapContext() {
	Dispose();
}

void BitmapContext::SetTarget(HDC const &target) {
	this->target = target;
}

void BitmapContext::Render() {
	//AlphaBlend(target, 0, 0, width, height, hDC, 0, 0, width, height, blend_function);
	BitBlt(target, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
}

void BitmapContext::SetSize(int width, int height) {
	Dispose();
	this->width = width;
	this->height = height;
	long const size = width * height * 4;
	data = new BYTE[size];
	memset(data, 0xffU, size);
	hBm = CreateBitmap(width, height, 1U, 32U, data);
	hDC = CreateCompatibleDC(target);
	SelectObject(hDC, hBm);
}
