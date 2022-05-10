#pragma once

#include "Graphics/common/type.hpp"
#include <set>

namespace Graphics {
	struct GraphicsContext;

	struct GraphicsTarget {
		friend struct GraphicsContext;
	protected:
		std::set<GraphicsContext *> contexts;
		
	public:

		struct Impl;
		Impl *impl;

		GraphicsTarget(Impl *impl);
		GraphicsTarget(Size2D size);
		~GraphicsTarget();

		Size2D Size() const;
		void Resize(Size2D size);
		void DrawOn(GraphicsTarget &target);
	};
}
