#pragma once

#include "../gdi.hpp"
#include "devicecontext.hpp"

namespace Crossant::Legacy {
	struct Bitmap : GDIObject {
		Size2D const size;
		DeviceContext &dc;

		Bitmap(Size2D size);
		Bitmap(DeviceContext &dc, Size2D size);
		virtual ~Bitmap() override;

		RectRange Range() const;
	};
}
