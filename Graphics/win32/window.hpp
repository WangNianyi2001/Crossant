#pragma once

#include "../window.hpp"
#include "legacy/user.hpp"
#include <map>

namespace Graphics::Win32 {
	class Window : public Graphics::Window {
	protected:
		Legacy::Window *const legacy;

	public:
		static std::map<void *, Window *> windowMap;
		static std::map<unsigned, WindowEventType> eventMap;

		Window(Legacy::Window::CreationArguments arguments);

		virtual ~Window() override;

		virtual void Quit() override;

		long ByPass(Legacy::Window::Event event);
	};
}
