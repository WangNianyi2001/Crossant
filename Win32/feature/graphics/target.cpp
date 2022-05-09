#include "target.hpp"

using namespace Graphics;

GraphicsTarget::GraphicsTarget(Vector2U size) : impl(new Impl(size)) {}

GraphicsTarget::~GraphicsTarget() {
	delete impl;
}

Vector2U GraphicsTarget::GetSize() const {
	return impl->size;
}

void GraphicsTarget::Resize(Vector2U size) {
	delete impl;
	impl = new Impl(size);
}