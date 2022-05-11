#pragma once

namespace Crossant::Legacy {
	void TryThrowLastError();
	void ResolveLastError();

	struct HandledObject  {
		void *const handle;

		HandledObject(void *handle) : handle(handle) {}

		virtual ~HandledObject() = default;

		template<typename H>
		inline H GetHandle() const {
			if(this == nullptr)
				return nullptr;
			return reinterpret_cast<H>(handle);
		}
	};
}

#include "legacy/kernel.hpp"
#include "legacy/user.hpp"
#include "legacy/gdi.hpp"
