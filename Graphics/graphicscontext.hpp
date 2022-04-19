#pragma once

#include "common/subscriber.hpp"

namespace Graphics {
	template<typename Target>
	class GraphicsContext : public ConfigurableSubscriber<> {
	protected:
		GraphicsContext() = default;

	public:
		virtual ~GraphicsContext() = default;

		virtual void Begin() = 0;
		void Draw() {
			Begin();
			Push();
			End();
		}
		virtual void End() = 0;
	};
}
