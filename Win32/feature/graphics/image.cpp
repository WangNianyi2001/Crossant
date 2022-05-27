#pragma once

#include "Crossant/graphics/image.hpp"
#include <Windows.h>
#include "Win32/utility.hpp"

using namespace Crossant;
using namespace Crossant::Graphics;

Color ParseColor(Byte const *position, WORD byteCount) {
	Color color{};
	switch(byteCount) {
	default:
		color.a = 0;
		return color;
	case 3:
		color.r = ByteToChannel(position[2]);
		color.g = ByteToChannel(position[1]);
		color.b = ByteToChannel(position[0]);
		break;
	}
	return color;
}

Image *Image::FromBitmap(std::ifstream &fs) {
	if(!fs.is_open())
		return nullptr;

	BITMAPFILEHEADER header;
	fs.read((char *)&header, sizeof(BITMAPFILEHEADER));

	DWORD infoSize;
	fs.read((char *)&infoSize, sizeof(DWORD));
	fs.seekg(-(int)sizeof(DWORD), std::ios::cur);
	if(infoSize != sizeof(BITMAPINFOHEADER))
		return nullptr;

	BITMAPINFOHEADER info;
	fs.read((char *)&info, sizeof(BITMAPINFOHEADER));
	if(info.biCompression != BI_RGB)	// Non-compressed
		return nullptr;

	bool bottomUp = info.biHeight > 0;
	Size2D const size = { (unsigned)info.biWidth, (unsigned)std::abs(info.biHeight) };
	WORD byteCount = info.biBitCount >> 3;
	if(byteCount == 0)
		return nullptr;

	unsigned rowBytes = (byteCount * size[0] + 3U) & ~0x3U;
	unsigned bufferBytes = rowBytes * size[1];
	Byte *const buffer = new Byte[bufferBytes];
	fs.seekg(header.bfOffBits, std::ios::beg);
	fs.readsome((char *)buffer, bufferBytes);

	Image *image = new Image(size);

	Byte *currentLine = buffer;
	int const yIncr = bottomUp ? 1 : -1;
	unsigned imageY = bottomUp ? 0 : size[0] - 1;
	for(unsigned y = 0; y < size[1]; ++y, imageY += yIncr, currentLine += rowBytes) {
		for(unsigned x = 0; x < size[0]; ++x) {
			Color color = ParseColor(currentLine + x * byteCount, byteCount);
			Size2D imageCoord = { x, imageY };
			image->At(imageCoord) = color;
		}
	}

	return image;
}