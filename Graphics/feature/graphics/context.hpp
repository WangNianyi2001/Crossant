#pragma once

#include "Graphics/common/event/subscriber.hpp"
#include "Graphics/common/type.hpp"
#include "target.hpp"

namespace Graphics {
	struct GraphicsContext : ConfigurableSubscriber<> {
		GraphicsTarget &target;

		GraphicsContext(GraphicsTarget &target);
		virtual ~GraphicsContext() = default;

		virtual void MakeCurrent() const = 0;
		virtual void Resize(Size2D size) = 0;
	};
}

#include "context2d.hpp"
#include "context3d.hpp"
