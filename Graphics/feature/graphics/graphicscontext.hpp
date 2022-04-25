#pragma once

#include "../../common/event/subscriber.hpp"
#include "../../common/type.hpp"
#include "../graphics.hpp"

namespace Graphics {
	class GraphicsContext : public ConfigurableSubscriber<> {
	public:
		virtual ~GraphicsContext() = default;

		virtual void Resize(Vector2U size) = 0;
	};

	class GraphicsContext2D : public GraphicsContext {
	public:
		struct Impl;
		Impl *impl;

		GraphicsContext2D(Vector2U size);
		virtual ~GraphicsContext2D() override;

		virtual void Resize(Vector2U size) override;

		virtual void Pixel(Vector2F pos, Color color);
		virtual void SelectBrush(Brush *brush);
		virtual void SelectPen(Pen *pen);
	};

	class GraphicsContext3D : public GraphicsContext {
	};
}
