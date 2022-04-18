#pragma once

#include "../../drawingcontext.hpp"

#include <Windows.h>

#pragma comment(lib, "Msimg32.lib")

namespace Graphics::Win32 {
	class BitmapContext : public DrawingContext<HDC> {
		static BLENDFUNCTION blend_function;
	protected:
		HDC target;
		HBITMAP hBm = NULL;
		BYTE *data = nullptr;
		virtual void Dispose() override;
	public:
		int width, height;
		HDC hDC;
		virtual ~BitmapContext() override;
		virtual void SetTarget(HDC const &target) override;
		virtual void Render() override;
		virtual void SetSize(int width, int height) override;
	};
}
