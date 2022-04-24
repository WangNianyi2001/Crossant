#pragma once

namespace Graphics::Win32::Legacy {
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
