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

	struct HandledObject {
		void *const handle;

		HandledObject(void *const handle) : handle(handle) {}

		virtual ~HandledObject() = default;

		template<typename H>
		inline H GetHandle() const {
			if(this == nullptr)
				return nullptr;
			return reinterpret_cast<H>(handle);
		}
	};
}
