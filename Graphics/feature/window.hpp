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

	struct Application;

	struct Window : Listener<WindowEvent::Type, WindowEvent> {
		struct Impl;
		Impl *impl;

		GraphicsContext2D *gc2 = nullptr;

		Window(Application *application);
		virtual ~Window();

		// Life cycle
		bool Alive();
		void Live();
		void Kill();

		// Window state
		void Show();

		// Visual
		ScreenRect ClientRect();
		void Repaint();
	};
}
