#pragma once

#include "../gdi.hpp"
#include "devicecontext.hpp"

namespace Graphics::Legacy {
	struct Bitmap : GDIObject {
		Vector2U const size;
		DeviceContext &dc;

		Bitmap(Vector2U size);
		Bitmap(DeviceContext &dc);
		virtual ~Bitmap() override;
	};
}
