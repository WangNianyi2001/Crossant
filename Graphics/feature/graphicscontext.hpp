#pragma once

#include "../common/event/subscriber.hpp"
#include "../common/type.hpp"

namespace Graphics {
	class GraphicsContext : public ConfigurableSubscriber<> {
	protected:
		GraphicsContext() = default;

	public:
		virtual ~GraphicsContext() = default;

		virtual void Resize(Vector2U size) = 0;
	};

	class GraphicsContext2D : public GraphicsContext {
	public:
		virtual ~GraphicsContext2D() override = default;

		virtual void Pixel(Vector2F pos, Color color) = 0;
	};

	class GraphicsContext3D : public GraphicsContext {
	public:
		virtual ~GraphicsContext3D() override = default;
	};
}
