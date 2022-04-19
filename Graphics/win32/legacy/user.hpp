#pragma once

#include "../legacy.hpp"
#include "kernel.hpp"
#include "../../eventsystem/event.hpp"

namespace Graphics::Win32::Legacy {
	struct UserObject : HandledObject {
		UserObject(void *const handle) : HandledObject(handle) {}

		virtual ~UserObject() override = default;
	};

	struct ModuleInstance : UserObject {
		ModuleInstance(void *const handle) : UserObject(handle) {}
	};

	struct Menu : UserObject {
		Menu(void *const handle) : UserObject(handle) {}
	};

	struct WindowClass : Object {
		enum struct Style : unsigned long {
			VRedraw = 0x00000001,
			HRedraw = 0x00000002,
			Dblclks = 0x00000008,
			OwnDC = 0x00000020,
			ClassDC = 0x00000040,
			ParentDC = 0x00000080,
			NoClose = 0x00000200,
			SaveBits = 0x00000800,
			ByteAlignClient = 0x00001000,
			ByteAlignWindow = 0x00002000,
			GlobalClass = 0x00004000,
			IME = 0x00010000,
			DropShadow = 0x00020000,
		};

		struct Info {
			Style style = Style::ClassDC;
			void *process = nullptr;
			ModuleInstance *instance = nullptr;
			Icon *icon = nullptr;
			Cursor *cursor = nullptr;
			// Should be a brush
			// Forward declaration doesn't really work here
			HandledObject *brush = nullptr;
			String menuName = String();
			String className = String();
			Icon *smallIcon = nullptr;
		};

		unsigned short const id;
		Info const info;

		WindowClass(Info info);

		virtual ~WindowClass() override;
	};
}

#include "window.hpp"
