#pragma once

#include "common/interface.hpp"
#include "common/listener.hpp"

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
		public Listener<WindowEventType, WindowEvent>, public Destroyable {
	protected:
		Window() = default;

	public:
		virtual ~Window() = default;

		// Life cycle
		virtual bool Alive() = 0;
		virtual void Live() = 0;

		// Window state
		virtual void Show() = 0;
	};
}
