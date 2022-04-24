#pragma once

#include "../feature/window.hpp"
#include "legacy/user.hpp"
#include <functional>
#include <map>

namespace Graphics::Win32 {
	class Application;

	class GDIContext;

	class Window : public Graphics::Window {
		friend class GDIContext;

	protected:
		Application *const application;
		Legacy::Window *const legacy;
		bool alive;

	public:
		static std::map<void *, Window *> windowMap;
		static std::map<
			unsigned,
			std::function<WindowEvent(Legacy::Window::Event)>
		> eventConversion;

		Window(Application *application, Legacy::Window *legacy);

		virtual ~Window() override = default;

		__int64 ByPass(Legacy::Window::Event event);

		// Life cycle
		virtual bool Alive() override;
		virtual void Live() override;
		virtual void Kill() override;

		// Window state
		virtual void Show() override;

		// Visual
		virtual GraphicsContext2D *MakeGraphicsContext2D() override;
		virtual void Repaint() override;
	};
}
