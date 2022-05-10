#include "target.hpp"
#include "Graphics/feature/graphics/context.hpp"
#include <Windows.h>

using namespace Graphics;

GraphicsTarget::GraphicsTarget(Impl *impl) : impl(impl) {}
GraphicsTarget::GraphicsTarget(Size2D size) : impl(new Impl(size)) {}

GraphicsTarget::~GraphicsTarget() {
	delete impl;
}

Size2D GraphicsTarget::Size() const {
	return impl->size;
}

void GraphicsTarget::Resize(Size2D size) {
	delete impl;
	impl = new Impl(size);
	for(auto context : contexts)
		context->OnResize();
}

void GraphicsTarget::DrawOn(GraphicsTarget &target) {
	impl->dc.PutTo(target.impl->dc, target.impl->Range(), { 0, 0 });
}