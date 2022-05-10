#pragma once

#include "Graphics/common/type.hpp"

namespace Graphics {
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
