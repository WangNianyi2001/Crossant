#pragma once

#include "event.hpp"

namespace Graphics {
	enum struct WindowEventType {
		Update,
		Paint,
		Close,
	};

	struct WindowEvent : Event<WindowEventType> {
		WindowEvent(WindowEventType type) : Event(type) {}
	};

	class Window :
		public EventDistributor<WindowEventType, WindowEvent> {
	protected:
		Window() = default;

	public:
		virtual ~Window() = default;

		virtual bool Alive() = 0;
		virtual void Live() = 0;
		virtual void Destroy() = 0;

		virtual void Show() = 0;
		virtual void FinishPaint() = 0;
	};
}
