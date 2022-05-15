#pragma once

#include "basic.hpp"
#include <cmath>

namespace Crossant {
	struct Quaternion {
		Float re = 1;
		Coord3D im{ 0, 0, 0 };

		static Quaternion AxisAngle(Coord3D axis, Float angle) {
			angle *= .5f;
			return { std::cosf(angle), axis * (std::sinf(angle) / axis.Module()) };
		}

		static Quaternion Euler(Coord3D euler) {
			Coord3D cos = euler.Operate<Float>(std::cosf),
				sin = euler.Operate<Float>(std::sinf);
			Quaternion
				y{ cos[1], { 0, sin[1], 0 } },
				x{ cos[0], { sin[0], 0, 0 } },
				z{ cos[2], { 0, 0, sin[2] } };
			return y * x * z;
		}

		Float Module() const {
			return std::sqrtf(re * re + im.SquaredModule());
		}

		inline Quaternion operator*(Float scalor) const {
			return { re * scalor, im * scalor };
		}

		Quaternion operator*(Quaternion const &q) const {
			Float const a1 = re, b1 = im[0], c1 = im[1], d1 = im[2];
			Float const a2 = q.re, b2 = q.im[0], c2 = q.im[1], d2 = q.im[2];
			return {
				a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2,
				{
					a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2,
					a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2,
					a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2
				}
			};
		}

		inline Quaternion Invert() const {
			return Quaternion{ re, im * -1 } *(1 / Module());
		}

		inline Coord3D operator*(Coord3D const &coord) const {
			return (operator*(Quaternion{ 1, coord }) * Invert()).im;
		}
	};
}
