#pragma once

#include "Graphics/common/type.hpp"
#include "Graphics/common/event/listener.hpp"
#include "mouse.hpp"
#include "graphics/context.hpp"

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
			Paint,
		};

		Type type;
		Mouse mouse;
		Size2D clientSize;
	};

	struct Application;

	struct Window : Listener<WindowEvent::Type, WindowEvent> {
		struct Impl;
		Impl *impl;

		GraphicsTarget graphicsTarget;

		Window(Application *application);
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
