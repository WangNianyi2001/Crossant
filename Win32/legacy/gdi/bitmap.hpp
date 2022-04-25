#pragma once

#include "../gdi.hpp"
#include "devicecontext.hpp"

namespace Graphics::Legacy {
	struct Bitmap : GDIObject {
		Vector2U const size;
		DeviceContext *const dc;

		Bitmap(Vector2U size);
		virtual ~Bitmap() override;
	};
}
