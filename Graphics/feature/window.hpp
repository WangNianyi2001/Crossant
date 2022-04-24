#pragma once

#include "../common/type.hpp"
#include "../common/event/listener.hpp"
#include "../feature/mouse.hpp"
#include "graphicscontext.hpp"

namespace Graphics {
	struct WindowEvent {
		enum struct Type {
			// Life cycle
			Update,
			Close,

			// Mouse
			MouseMove,
			MouseDown,
			MouseUp,

			// Visual
			Paint,
		};

		Type type;
		Mouse mouse;
	};

	class Window : public Listener<WindowEvent::Type, WindowEvent> {
	protected:
		Window() = default;

	public:
		virtual ~Window() = default;

		// Life cycle
		virtual bool Alive() = 0;
		virtual void Live() = 0;
		virtual void Kill() = 0;

		// Window state
		virtual void Show() = 0;

		// Visual
		virtual ScreenRect ClientRect() = 0;
		virtual GraphicsContext2D *MakeGraphicsContext2D() = 0;
		virtual void Repaint() = 0;
	};
}
