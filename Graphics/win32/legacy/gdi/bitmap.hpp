#pragma once

#include "../gdi.hpp"

namespace Graphics::Win32::Legacy {
	struct Bitmap : GDIObject {
		Vector2U const size;

		Bitmap(Vector2U size);
		virtual ~Bitmap() override;
	};
}
