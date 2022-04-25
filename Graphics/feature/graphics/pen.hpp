#pragma once

#include "../../common/type.hpp"

namespace Graphics {
	class Pen {
	public:
		struct Impl;
		Impl *impl;

		Pen();
		virtual ~Pen();
	};

	class SimplePen : public Pen {
	public:
		SimplePen(unsigned width, Color color);
		virtual ~SimplePen() override;
	};
}
