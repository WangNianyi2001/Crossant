#include "..\..\..\Graphics\feature\graphics\pen.hpp"
#include "pen.hpp"
#include <Windows.h>

using namespace Graphics;

std::map<Pen::Style, int> Pen::Impl::styleMap{
	{ Style::Solid, PS_SOLID },
	{ Style::Dash, PS_DASH },
	{ Style::Dot, PS_DOT },
	{ Style::DashDot, PS_DASHDOT },
	{ Style::DashDotDot, PS_DASHDOTDOT },
};

std::map<Pen::Cap, int> Pen::Impl::capMap{
	{ Cap::Round, PS_ENDCAP_ROUND },
	{ Cap::Square, PS_ENDCAP_SQUARE },
	{ Cap::Flat, PS_ENDCAP_FLAT },
};

std::map<Pen::Join, int> Pen::Impl::joinMap{
	{ Join::Round, PS_JOIN_ROUND },
	{ Join::Miter, PS_JOIN_MITER },
	{ Join::Bevel, PS_JOIN_BEVEL },
};

Pen::Pen() {
	impl = new Impl{};
}

Pen::Pen(int width, Color color,
	Style style, Cap cap, Join join)
	: Pen() {
	LOGBRUSH log{ BS_SOLID, Legacy::ColorRef(color).value };
	HPEN hPen = ExtCreatePen(
		PS_GEOMETRIC,
		width,
		&log,
		impl->styleMap[style],
		NULL
	);
	impl->pen = new Legacy::Pen(hPen);
}

Pen::~Pen() {
	delete impl->pen;
	delete impl;
}
