#pragma once

#include "../image.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct Texture {
		unsigned const id;
		Image const &image;

		Texture(Image const &image);

		void Apply() const;
	};
}