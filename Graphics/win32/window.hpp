#pragma once

#include "../window.hpp"
#include "legacy/user.hpp"
#include <map>

namespace Graphics::Win32 {
	class Window : public Graphics::Window {
	protected:
		Legacy::Window *const legacy;
		bool alive;

	public:
		static std::map<void *, Window *> windowMap;
		static std::map<unsigned, WindowEventType> eventMap;

		Window(Legacy::Window::CreationArguments arguments);

		virtual ~Window() = default;

		__int64 ByPass(Legacy::Window::Event event);

		virtual bool Alive() override;
		virtual void Live() override;
		virtual void Destroy() override;

		virtual void Show() override;
		virtual void FinishPaint() override;
	};
}
