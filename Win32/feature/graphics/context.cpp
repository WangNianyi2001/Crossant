#include "Crossant/feature/graphics/context.hpp"

using namespace Crossant::Graphics;

Context::Context(Target &target) : target(target) {
	target.contexts.insert(this);
}

Context::~Context() {
	auto &set = target.contexts;
	auto it = set.find(this);
	if(it != set.end())
		set.erase(it);
}
