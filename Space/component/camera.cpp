#include "camera.hpp"
#include "meshrenderer.hpp"

using namespace Crossant::Graphics::Graphics3D;

void Camera::Render() {
	Space &space = object.space;

	// Push projection
	space.SetMatrixMode(Space::MatrixMode::Projection);
	space.PushMatrix();

	// Overwrite projection
	space.LoadIdentity();
	auto size = space.target.Size();
	float aspect = (float)size[0] / size[1];
	space.Perspective(fov, aspect, .1f, 1e2);

	// Push space
	space.SetMatrixMode(Space::MatrixMode::Space);
	space.PushMatrix();

	// Overwrite space
	space.LoadIdentity();
	object.transform.ApplyInverse();

	// Render
	for(Renderer *renderer : space.ComponentsOf<Renderer>())
		renderer->Render();

	// Restore space
	space.PopMatrix();

	// Restore projection
	space.SetMatrixMode(Space::MatrixMode::Projection);
	space.PopMatrix();
}