#include "target.hpp"
#include "Crossant/feature/graphics/context.hpp"
#include <Windows.h>

using namespace Crossant::Graphics;

Target::Target(Impl *impl) : impl(impl) {}
Target::Target(Size2D size) : impl(new Impl(size)) {}

Target::~Target() {
	delete impl;
}

Crossant::Size2D Target::Size() const {
	return impl->size;
}

void Target::Resize(Size2D size) {
	delete impl;
	impl = new Impl(size);
	for(auto context : contexts)
		context->OnResize();
}

void Target::DrawOn(Target &target) {
	impl->dc.PutTo(target.impl->dc, target.impl->Range(), { 0, 0 });
}
