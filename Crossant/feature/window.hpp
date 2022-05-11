#pragma once

#include "Crossant/common/type.hpp"
#include "Crossant/common/event/listener.hpp"
#include "mouse.hpp"
#include "graphics/context.hpp"

namespace Crossant {
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
			Draw,
		};

		Type type;
		Mouse mouse;
		Size2D clientSize;
	};

	struct Application;

	struct Window : Listener<WindowEvent::Type, WindowEvent> {
		struct Impl;
		Impl *impl;

		Graphics::Target graphicsTarget;

		Window(Application &application);
		virtual ~Window();

		// Life cycle
		bool Alive();
		void Live();
		void Kill();

		// Window state
		void Show();

		// Visual
		RectRange ClientRect();
		void Repaint();
	};
}
