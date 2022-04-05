#include "bitmap.hpp"

using namespace Graphics::Win32;

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
