#pragma once

#include <xstring>

namespace Graphics::Win32::Legacy {
	using Char =
#ifdef UNICODE
		wchar_t
#else
		char
#endif
	;
	using String = std::basic_string<Char>;

	void TryThrowLastError();

	struct Object {
		virtual ~Object() = default;
	};

	struct HandledObject : Object {
		void *const handle;

		HandledObject(void *const handle) : handle(handle) {}

		virtual ~HandledObject() = default;
	};
}
