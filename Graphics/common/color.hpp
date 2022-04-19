#pragma once

namespace Graphics {
	template<typename Channel, int count>
	using Color = Channel[count];

	using Color3F = Color<float, 3>;
	using Color3B = Color<unsigned __int8, 3>;
}
