#pragma once

#include "context.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct Drawable {
		virtual ~Drawable() = default;

		virtual void Draw(Context &context) const = 0;
	};
}
