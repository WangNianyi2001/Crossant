#pragma once

#include "../../common/type.hpp"

namespace Graphics {
	class Pen {
	protected:
		Pen();

	public:
		struct Impl;
		Impl *impl;

		enum struct Style {
			Solid,
			Dash,
			Dot,
			DashDot,
			DashDotDot,
		};
		Style style;

		enum struct Cap {
			Round, Square, Flat
		};
		Cap cap;

		enum struct Join {
			Bevel, Miter, Round
		};
		Join join;

		Pen(int width,
			Color color,
			Style style = Style::Solid,
			Cap cap = Cap::Flat,
			Join join = Join::Miter);
		virtual ~Pen();
	};
}
