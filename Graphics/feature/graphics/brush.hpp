#pragma once

#include "../../common/type.hpp"

namespace Graphics {
	class Brush {
	public:
		struct Impl;
		Impl *impl;

		Brush();

		virtual ~Brush();
	};

	class SolidBrush : public Brush {
		SolidBrush(Color color);
		virtual ~SolidBrush() override;
	};
}
