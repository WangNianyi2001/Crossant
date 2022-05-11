#include "pen.hpp"
#include <Windows.h>

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
	impl->pen = new Legacy::Pen(GetStockObject(NULL_PEN));
}

SimplePen::SimplePen(Color color, Style style) : style(style) {
	HPEN hPen = CreatePen(
		impl->styleMap[style], 1,
		Legacy::ColorRef(color).value
	);
	impl->pen = new Legacy::Pen(hPen);
}

SimplePen::~SimplePen() {
	delete impl->pen;
}

SolidPen::SolidPen(
	Color color, int width,
	Style style, Cap cap, Join join
) : style(style), cap(cap), join(join) {
	LOGBRUSH log{ BS_SOLID, Legacy::ColorRef(color).value };
	HPEN hPen = ExtCreatePen(
		PS_GEOMETRIC |
		impl->styleMap[style] | impl->capMap[cap] | impl->joinMap[join],
		width, &log, 0, NULL
	);
	impl->pen = new Legacy::Pen(hPen);
}

SolidPen::~SolidPen() {
	delete impl->pen;
}
