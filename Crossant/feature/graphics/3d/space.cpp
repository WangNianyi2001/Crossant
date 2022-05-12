#include "space.hpp"

using namespace Crossant::Graphics::Graphics3D;

void Transform::Apply() const {
	if(parent != nullptr)
		parent->Apply();
	object.space.Translate(translation);
	object.space.Rotate(rotation);
	object.space.Scale(scalor);
}