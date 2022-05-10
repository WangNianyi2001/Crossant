#pragma once

#include "../gdi.hpp"

namespace Graphics::Legacy {
	struct DeviceContext : HandledObject {
		bool const isPrivate;

		DeviceContext(
			void *const handle,
			bool isPrivate = true
		) : HandledObject(handle), isPrivate(isPrivate) {
			Legacy::TryThrowLastError();
		}
		virtual ~DeviceContext() override;

		void PutTo(DeviceContext &dest,
			RectRange const &clip,
			Coord2D const &offset
		) const;
		void Select(GDIObject *object);

		void SetPixel(int x, int y, ColorRef color);
		void Rectangle(int left, int top, int right, int bottom);
	};
}
