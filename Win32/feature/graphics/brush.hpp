#include "..\..\..\Graphics\feature\graphics\brush.hpp"
#include "..\..\..\Graphics\feature\graphics\brush.hpp"
#pragma once

#include "Graphics/graphics.hpp"
#include "../../legacy.hpp"

namespace Graphics {
	struct Brush::Impl {
		Legacy::Brush *brush;
	};

	Brush::Brush() {
		impl = new Impl{};
	}

	Brush::~Brush() {
		delete impl;
	}

	SolidBrush::SolidBrush(Color color) {
		impl->brush = new Legacy::SolidBrush(Legacy::ColorRef(color));
	}

	SolidBrush::~SolidBrush() {
		delete impl->brush;
	}
}
