#include "pen.hpp"
#include <Windows.h>
#include "Win32/utility.hpp"

using namespace Crossant::Graphics::Graphics2D;

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

Pen::~Pen() {
	delete impl;
}

NullPen::NullPen() {
	impl->hPen = (HPEN)GetStockObject(NULL_PEN);
}

SimplePen::SimplePen(Color color, Style style) : style(style) {
	impl->hPen = CreatePen(
		impl->styleMap[style], 1,
		ColorToRef(color)
	);
}

SimplePen::~SimplePen() {
	DeleteObject(impl->hPen);
}

SolidPen::SolidPen(
	Color color, int width,
	Style style, Cap cap, Join join
) : style(style), cap(cap), join(join) {
	LOGBRUSH log{ BS_SOLID, ColorToRef(color) };
	impl->hPen = ExtCreatePen(
		PS_GEOMETRIC |
		impl->styleMap[style] | impl->capMap[cap] | impl->joinMap[join],
		width, &log, 0, NULL
	);
}

SolidPen::~SolidPen() {
	DeleteObject(impl->hPen);
}
