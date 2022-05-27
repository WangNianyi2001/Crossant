#pragma once

#include "Crossant/common/basic.hpp"
#include <fstream>

namespace Crossant::Graphics {
	struct Image {
		static Image *FromBitmap(std::ifstream &bitmap);

		Size2D const size;
		Color *const pixels;

	protected:
		inline unsigned CoordToIndex(Size2D at) const {
			return at[1] * size[0] + at[0];
		}

	public:
		Image(Size2D size) : size(size), pixels(new Color[size[0] * size[1]]) {}

		~Image() {
			delete[] pixels;
		}

		inline bool InRange(Size2D at) const noexcept {
			return at <= size;
		}

		Color Get(Size2D at) const noexcept {
			if(!InRange(at))
				return Color{};
			return pixels[CoordToIndex(at)];
		}

		Color &At(Size2D at) const {
			if(!InRange(at))
				throw nullptr;
			return pixels[CoordToIndex(at)];
		}
	};
}