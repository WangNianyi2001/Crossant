#include "target.hpp"

using namespace Graphics;

GraphicsTarget::GraphicsTarget(Vector2U size) {
	impl = new Impl{};
}

GraphicsTarget::~GraphicsTarget() {
	delete impl->bitmap;
	delete impl;
}

Vector2U GraphicsTarget::GetSize() const {
	return impl->bitmap->size;
}

void GraphicsTarget::Resize(Vector2U size) {
	delete impl->bitmap;
	impl->bitmap = new Legacy::Bitmap(size);
}