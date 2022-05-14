#pragma once

#include "Crossant/common/listener.hpp"
#include "mouse.hpp"
#include "keyboard.hpp"
#include "graphics/context.hpp"

namespace Crossant {
	int Main();
	
	struct Window;

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

			// Keyboard
			KeyDown,
			KeyUp,

			// Visual
			Draw,
		};

		Window *window;
		Type type;
		Mouse::Button mouseButton;
		Keyboard::Key key;
	};

	struct Window : Listener<WindowEvent::Type, WindowEvent> {
		using Event = WindowEvent;

		struct Impl;
		Impl *impl;

		Graphics::Target graphicsTarget;

		Window();
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
