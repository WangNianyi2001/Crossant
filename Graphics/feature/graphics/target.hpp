#pragma once

#include "../../common/type.hpp"

namespace Graphics {
	struct GraphicsTarget {
		struct Impl;
		Impl *impl;

		GraphicsTarget(Impl *impl);
		GraphicsTarget(Vector2U size);
		~GraphicsTarget();

		Vector2U GetSize() const;
		void Resize(Vector2U size);
	};
}
