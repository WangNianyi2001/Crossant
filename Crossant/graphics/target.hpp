#pragma once

#include "Crossant/common/basic.hpp"
#include <set>

namespace Crossant::Graphics {
	struct Context;

	struct Target {
		friend struct Context;
	protected:
		std::set<Context *> contexts;
		
	public:

		struct Impl;
		Impl *impl;

		Target(Impl *impl);
		Target(Size2D size = { 1, 1 });
		~Target();

		Size2D Size() const;
		void Resize(Size2D size);
		void DrawOn(Target &target);
	};
}
