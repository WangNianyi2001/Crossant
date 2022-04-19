#pragma once

#include "../window.hpp"
#include "legacy/user.hpp"
#include <functional>
#include <map>

namespace Graphics::Win32 {
	class GDIContext;

	class Window : public Graphics::Window {
		friend class GDIContext;

	protected:
		Legacy::Window *const legacy;
		bool alive;

	public:
		static std::map<void *, Window *> windowMap;
		static std::map<
			unsigned,
			std::function<WindowEvent(Legacy::Window::Event)>
		> eventConversion;

		Window(Legacy::Window::CreationArguments arguments);

		virtual ~Window() override = default;

		__int64 ByPass(Legacy::Window::Event event);

		// Life cycle
		virtual bool Alive() override;
		virtual void Live() override;
		virtual void Destroy() override;

		// Window state
		virtual void Show() override;
	};
}
