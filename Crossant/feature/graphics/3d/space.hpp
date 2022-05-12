#pragma once

#include "context.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct Transform {
		Transform *parent = nullptr;
		Coord3D translation;
	};

	struct Space : Context {
		Space(Target &target) : Context(target) {}
	};

	struct Object {};
}