#pragma once

#include "../common/subscriber.hpp"
#include "../common/types.hpp"

namespace Graphics {
	template<typename Target>
	class GraphicsContext : public ConfigurableSubscriber<> {
	protected:
		GraphicsContext() = default;

	public:
		virtual ~GraphicsContext() = default;

		void Configure(std::function<void()> action) {
			ConfigurableSubscriber<>::Configure(action);
		}

		virtual void Resize(Vector2U size) = 0;
	};
}
