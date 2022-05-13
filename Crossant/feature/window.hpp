#pragma once

#include "Crossant/common/type.hpp"
#include "Crossant/common/event/listener.hpp"
#include "graphics/context.hpp"
#include <map>

namespace Crossant {
	struct Mouse {
		enum struct Button : Byte {
			Left, Middle, Right
		};
		std::map<Button, bool> buttons;
		Coord2D position;
	};
	
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

			// Visual
			Draw,
		};

		Window *window;
		Type type;
		Mouse::Button mouseButton;
	};

	struct Application;

	struct Window : Listener<WindowEvent::Type, WindowEvent> {
		using Event = WindowEvent;

		struct Impl;
		Impl *impl;

		Graphics::Target graphicsTarget;
		Mouse mouse;

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
