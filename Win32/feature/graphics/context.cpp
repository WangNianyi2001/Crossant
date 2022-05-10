#include "Graphics/feature/graphics/context.hpp"

using namespace Graphics;

GraphicsContext::GraphicsContext(GraphicsTarget &target) : target(target) {
	target.contexts.insert(this);
}

GraphicsContext::~GraphicsContext() {
	auto &set = target.contexts;
	auto it = set.find(this);
	if(it != set.end())
		set.erase(it);
}