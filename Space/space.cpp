#include "space.hpp"

using namespace Crossant::Space;

void Object::Transform::Apply() const {
	if(parent != nullptr)
		parent->Apply();
	object.parent.Translate(translation);
	object.parent.Rotate(rotation);
	object.parent.Scale(scalor);
}

void Object::Transform::ApplyInverse() const {
	Coord3D invScalor = { 1 / scalor[0], 1 / scalor[1], 1 / scalor[2] };
	object.parent.Scale(invScalor);
	object.parent.Rotate({ rotation.re, rotation.im * -1 });
	object.parent.Translate(translation * -1);
	if(parent != nullptr)
		parent->ApplyInverse();
}