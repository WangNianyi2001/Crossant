#pragma once

#include "../common/interface.hpp"
#include "../common/listener.hpp"
#include "../feature/mouse.hpp"
#include "graphicscontext.hpp"

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

		// Visual
		virtual GraphicsContext2D *MakeGraphicsContext2D() = 0;
		virtual void Repaint() = 0;
	};
}
