#pragma once

#include "../../common/event/subscriber.hpp"
#include "../../common/type.hpp"
#include "target.hpp"

namespace Graphics {
	struct GraphicsContext : ConfigurableSubscriber<> {
		GraphicsTarget &target;

		GraphicsContext(GraphicsTarget &target);
		virtual ~GraphicsContext() = default;

		virtual void MakeCurrent() const = 0;
		virtual void Resize(Vector2U size) = 0;
	};
}

#include "context2d.hpp"
#include "context3d.hpp"
