#include "space.hpp"

using namespace Crossant::Graphics::Graphics3D;

void Object::Transform::Apply() const {
	if(parent != nullptr)
		parent->Apply();
	object.parent.Translate(translation);
	object.parent.Rotate(rotation);
	object.parent.Scale(scalor);
}