#pragma once

#include "../common/type.hpp"
#include "../common/event/listener.hpp"
#include "mouse.hpp"
#include "graphics.hpp"

namespace Graphics {
	struct WindowEvent {
		enum struct Type {
			// Life cycle
			Update,
			Close,

			// Window state
			Resize,

			// Mouse
			MouseMove,
			MouseDown,
			MouseUp,

			// Visual
			Graph,
		};

		Type type;
		Mouse mouse;
		Vector2U clientSize;
	};

	class Application;

	class Window : public Listener<WindowEvent::Type, WindowEvent> {
	public:
		struct Impl;
		Impl *impl;

		GraphicsContext2D *gc2 = nullptr;

		Window(Application *application);
		virtual ~Window();

		// Life cycle
		virtual bool Alive();
		virtual void Live();
		virtual void Kill();

		// Window state
		virtual void Show();

		// Visual
		virtual ScreenRect ClientRect();
		virtual void Repaint();
	};
}
