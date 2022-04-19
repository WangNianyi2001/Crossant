#pragma once

#include "eventsystem/subscriber.hpp"

namespace Graphics {
	template<typename Target>
	class DrawingContext : public ConfigurableSubscriber<> {
	protected:
		DrawingContext() = default;

	public:
		virtual ~DrawingContext() = default;

		virtual void Draw() = 0;
	};
}
