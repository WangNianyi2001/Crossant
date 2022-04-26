#pragma once

#include "../../win32.hpp"

namespace Graphics {
	struct GraphicsContext2D::Impl {
		Window *window = nullptr;
		Legacy::Bitmap *bitmap = nullptr;
	};

	struct BrushBuffer : SingleBuffer<Brush *> {
	};

	struct BrushDoubleBuffer : DoubleBuffer<Brush *> {
		GraphicsContext2D *const gc;

		BrushDoubleBuffer(GraphicsContext2D *gc) : gc(gc) {}

		void Select() {
			if(!HasValue())
				return;	// Should select null brush here
			if(gc->impl->bitmap == nullptr)
				return;
			gc->impl->bitmap->dc->Select(
				Get().value()->impl->brush
			);
		}

		virtual void Swap() override {
			DoubleBuffer::Swap();
			Select();
		}

		virtual std::optional<Brush *> Push(
			Brush *const &newValue
		) override {
			auto ret = DoubleBuffer::Push(newValue);
			Select();
			return ret;
		}
	};
}
