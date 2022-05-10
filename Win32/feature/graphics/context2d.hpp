#pragma once

#include "Graphics/feature/graphics/context2d.hpp"
#include "target.hpp"
#include "context2d/brush.hpp"
#include "context2d/pen.hpp"

namespace Graphics {
	template<
		typename T,
		std::derived_from<Function<Legacy::GDIObject *, T>> Getter
	> struct GraphicsObjectBuffer : DoubleBuffer<T> {
		GraphicsContext2D &gc;

		GraphicsObjectBuffer(GraphicsContext2D &gc) : gc(gc) {}

		void Select() {
			if(!DoubleBuffer<T>::HasValue())
				return;
			if(gc.target.impl == nullptr)
				return;
			gc.target.impl->dc.Select(
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
