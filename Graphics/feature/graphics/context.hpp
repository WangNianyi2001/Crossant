#pragma once

#include "../../common/event/subscriber.hpp"
#include "../../common/type.hpp"
#include "../graphics.hpp"

namespace Graphics {
	struct GraphicsContext : ConfigurableSubscriber<> {
		virtual ~GraphicsContext() = default;

		virtual void Resize(Vector2U size) = 0;
	};
}

#include "context2d.hpp"
#include "context3d.hpp"
