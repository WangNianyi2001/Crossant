#pragma once

#include "event.hpp"

namespace Graphics {
	enum struct WindowEventType {
		Close,
	};

	struct WindowEvent : Event<WindowEventType> {};

	class Window :
		public EventDistributor<WindowEventType, WindowEvent> {
	protected:
		Window() = default;

	public:
		virtual ~Window() = default;

		virtual void Quit() = 0;
	};
}
