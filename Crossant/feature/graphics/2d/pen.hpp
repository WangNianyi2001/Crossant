#pragma once

#include "Crossant/common/type.hpp"

namespace Crossant::Graphics2D {
	struct Pen {
		struct Impl;
		Impl *impl;

		enum struct Style {
			Solid,
			Dash,
			Dot,
			DashDot,
			DashDotDot,
		};

		enum struct Cap {
			Round, Square, Flat
		};

		enum struct Join {
			Bevel, Miter, Round
		};

		Pen();
		virtual ~Pen();
	};

	struct NullPen : Pen {
		NullPen();
	};

	struct SimplePen : Pen {
		Style style;

		SimplePen(Color color, Style style = Style::Solid);
		virtual ~SimplePen() override;
	};

	struct SolidPen : Pen {
		Style style;
		Cap cap;
		Join join;

		SolidPen(
			Color color, int width = 1,
			Style style = Style::Solid,
			Cap cap = Cap::Flat,
			Join join = Join::Miter
		);
		virtual ~SolidPen() override;
	};
}
