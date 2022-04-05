#pragma once

#include "../graphics.hpp"

#include <Windows.h>

#pragma comment(lib, "Msimg32.lib")

namespace Graphics {
	namespace Win32 {
		class BitmapContext : public Context<HDC> {
		protected:
			int width, height;
			HDC target, hDC;
			HBITMAP hBm = NULL;
			BYTE *data = nullptr;
			virtual void Dispose() override;
		public:
			virtual ~BitmapContext() override;
			virtual void SetTarget(HDC const &target) override;
			virtual void Render() override = 0;
			virtual void SetSize(int width, int height) override;
		};
	}
}
