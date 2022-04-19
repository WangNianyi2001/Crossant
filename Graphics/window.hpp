#pragma once

#include "event.hpp"

namespace Graphics {
	enum struct WindowEventType {
		Close,
		Destroy
	};

	struct WindowEvent : Event<WindowEventType> {};

	class Window :
		public EventDistributor<WindowEventType, WindowEvent> {
	protected:
		Window() = default;

	public:
		virtual ~Window() = default;

		virtual void Show() = 0;
		virtual bool Alive() = 0;
		virtual void Live() = 0;
		virtual void Destroy() = 0;
	};
}
