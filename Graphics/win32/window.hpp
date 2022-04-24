#pragma once

#include "../feature/window.hpp"
#include "legacy/user.hpp"
#include "application.hpp"
#include <functional>
#include <map>

namespace Graphics::Win32 {
	class Application;

	class GDIContext;

	class Window : public Graphics::Window {
		friend class Application;
		friend class GDIContext;

	protected:
		static std::map<void *, Window *> windowMap;

		static std::map<
			unsigned,
			std::function<WindowEvent(Legacy::Window::Event)>
		> eventConversion;

		static inline Legacy::Window::Class *defaultClass = nullptr;

		static __int64 __stdcall MsgProc(void *hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam);

		Legacy::Window *const legacy;
		bool alive;

		__int64 ByPass(Legacy::Window::Event event);

	public:

		Window(Legacy::Window *legacy);
		Window(Application *application);

		virtual ~Window() override = default;

		// Life cycle
		virtual bool Alive() override;
		virtual void Live() override;
		virtual void Kill() override;

		// Window state
		virtual void Show() override;

		// Visual
		virtual ScreenRect ClientRect() override;
		virtual GraphicsContext2D *MakeGraphicsContext2D() override;
		virtual void Repaint() override;
	};
}
