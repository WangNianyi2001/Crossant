#pragma once

#include "../gdi.hpp"

namespace Graphics::Legacy {
	struct DeviceContext : HandledObject {
		bool const isPrivate;

		DeviceContext(
			void *const handle,
			bool isPrivate = true
		) : HandledObject(handle), isPrivate(isPrivate) {}
		virtual ~DeviceContext() override;

		void PutTo(DeviceContext *dest,
			ScreenRect const &clip,
			ScreenCoord const &offset
		);
		void Select(GDIObject *object);

		void SetPixel(int x, int y, ColorRef color);
		void Rect(int left, int top, int right, int bottom);
	};
}
