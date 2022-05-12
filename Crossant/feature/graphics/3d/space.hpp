#pragma once

#include "context.hpp"
#include "Crossant/common/type/quaternion.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct Transform {
		Transform *parent = nullptr;
		Coord3D translation{ 0, 0, 0 };
		Quaternion rotation{ 1, { 0, 0, 0 } };
		Coord3D scalor{ 1, 1, 1 };

		void Apply(Context &context) const {
			context.Scale(scalor);
			context.Rotate(rotation);
			context.Translate(translation);
			if(parent != nullptr)
				parent->Apply(context);
		}
	};

	struct Space : Context {
		Space(Target &target) : Context(target) {}
	};

	struct Object {
		Transform localTransform;
	};
}