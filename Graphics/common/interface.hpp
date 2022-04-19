#pragma once

namespace Graphics {
	struct Destroyable {
		virtual void Destroy() = 0;
	};
}
