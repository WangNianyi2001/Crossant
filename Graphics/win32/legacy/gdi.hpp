#pragma once

#include "../../common/type.hpp"
#include "../legacy.hpp"
#include "user.hpp"

namespace Graphics::Win32::Legacy {
	struct ColorRef {
		using Hex = unsigned long;

		static inline Hex Channel(Color const &color, unsigned i) {
			return ((Hex)(0xffU * color[i]) & 0xffU);
		}

		static inline Hex ToHex(Color const &color) {
			return Channel(color, 0) |
				(Channel(color, 1) << 8) |
				(Channel(color, 2) << 16);
		}

		Hex const value;

		ColorRef(Color color) : value(ToHex(color)) {}
	};

	struct GDIObject : HandledObject {
		GDIObject(void *const handle) : HandledObject(handle) {}
	};

	struct DeviceContext;

	struct PaintStruct {
		void *const ps;

		PaintStruct();
		~PaintStruct();

		DeviceContext *GetDC();
	};
}

#include "gdi/bitmap.hpp"
#include "gdi/devicecontext.hpp"
