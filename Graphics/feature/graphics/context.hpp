#pragma once

#include "Graphics/common/event/subscriber.hpp"
#include "Graphics/common/type.hpp"
#include "target.hpp"

namespace Graphics {
	struct GraphicsContext {
		GraphicsTarget &target;

		GraphicsContext(GraphicsTarget &target);
		virtual ~GraphicsContext();

		virtual void MakeCurrent() const = 0;
		virtual void OnResize() = 0;
	};
}
