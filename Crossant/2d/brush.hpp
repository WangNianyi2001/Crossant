#pragma once

#include "Crossant/common/basic.hpp"

namespace Crossant::Graphics::Graphics2D {
	struct Brush {
		struct Impl;
		Impl *impl;

		Brush();
		virtual ~Brush();
	};

	struct NullBrush : Brush {
		NullBrush();
	};

	struct SolidBrush : Brush {
		SolidBrush(Color color);
		virtual ~SolidBrush() override;
	};
}
