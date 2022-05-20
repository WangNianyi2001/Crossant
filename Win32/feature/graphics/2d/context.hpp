#pragma once

#include "Crossant/feature/graphics/2d/context.hpp"
#include "../target.hpp"
#include "brush.hpp"
#include "pen.hpp"

namespace Crossant::Graphics::Graphics2D {
	template<typename T, typename Getter>
	struct GraphicsObjectBuffer : DoubleBuffer<T> {
		Context &gc;

		GraphicsObjectBuffer(Context &gc) : gc(gc) {}

		void Select() {
			if(!DoubleBuffer<T>::HasValue())
				return;
			if(gc.target.impl == nullptr)
				return;
			SelectObject(
				gc.target.impl->hDC,
				Getter{}(DoubleBuffer<T>::Get().value())
			);
		}

		virtual void Swap() override {
			DoubleBuffer<T>::Swap();
			Select();
		}

		virtual std::optional<T> Push(
			T const &newValue
		) override {
			auto ret = DoubleBuffer<T>::Push(newValue);
			Select();
			return ret;
		}
	};

	using BrushBuffer = GraphicsObjectBuffer<Brush *,
		Brush::Impl::Getter>;

	using PenBuffer = GraphicsObjectBuffer<Pen *,
		Pen::Impl::Getter>;
}
