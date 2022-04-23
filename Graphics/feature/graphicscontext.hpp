#pragma once

#include "../common/subscriber.hpp"
#include "../common/types.hpp"

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

		virtual void Pixel(Vector2F pos, Color3B color) = 0;
	};

	class GraphicsContext3D : public GraphicsContext {
	public:
		virtual ~GraphicsContext3D() override = default;
	};
}
