#pragma once

#include "../common/interface.hpp"
#include "../common/listener.hpp"
#include "../feature/mouse.hpp"

namespace Graphics {
	struct WindowEvent {
		enum struct Type {
			// Life cycle
			Update,
			Close,

			// Mouse
			MouseDown,
			MouseUp,

			// Visual
			Paint,
		};

		Type type;
		Mouse mouse;
	};

	class Window :
		public Listener<WindowEvent::Type, WindowEvent>,
		public Destroyable {
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
