#pragma once

#include "Graphics/common/type.hpp"

namespace Graphics {
	struct GraphicsTarget {
		struct Impl;
		Impl *impl;

		GraphicsTarget(Impl *impl);
		GraphicsTarget(Size2D size);
		~GraphicsTarget();

		Size2D GetSize() const;
		void Resize(Size2D size);
	};
}
