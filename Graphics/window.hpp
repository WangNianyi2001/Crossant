#pragma once

#include "eventsystem/event.hpp"

namespace Graphics {
	enum struct WindowEventType {
		Update,
		Paint,
		Close,
	};

	struct WindowEvent {
		WindowEventType type;
	};

	class Window :
		public EventListener<WindowEventType, WindowEvent> {
	protected:
		Window() = default;

	public:
		virtual ~Window() = default;

		// Life cycle
		virtual bool Alive() = 0;
		virtual void Live() = 0;
		virtual void Destroy() = 0;

		// Window state
		virtual void Show() = 0;
	};
}
