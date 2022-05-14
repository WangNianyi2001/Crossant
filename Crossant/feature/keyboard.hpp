#pragma once

#include "Crossant/common/basic.hpp"

namespace Crossant {
	struct Keyboard {
		enum struct Key : Byte {
			Unrecognized,
			Num0 = '0', Num1, Num2, Num3, Num4,
			Num5, Num6, Num7, Num8, Num9,
			A = 'A', B, C, D, E, F, G, H, I, J, K, L, M,
			N, O, P, Q, R, S, T, U, V, W, X, Y, Z
		};

		static bool Pressed(Key key);
	};
}