#include "target.hpp"

using namespace Graphics;

GraphicsTarget::GraphicsTarget(Impl *impl) : impl(impl) {}
GraphicsTarget::GraphicsTarget(Size2D size) : impl(new Impl(size)) {}

GraphicsTarget::~GraphicsTarget() {
	delete impl;
}

Size2D GraphicsTarget::GetSize() const {
	return impl->size;
}

void GraphicsTarget::Resize(Size2D size) {
	delete impl;
	impl = new Impl(size);
}