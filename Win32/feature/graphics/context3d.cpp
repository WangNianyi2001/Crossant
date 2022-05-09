#include "context3d.hpp"

using namespace Graphics;

GraphicsContext3D::GraphicsContext3D(GraphicsTarget &target) : GraphicsContext(target) {
	impl = new Impl{};

	PIXELFORMATDESCRIPTOR descriptor;
	memset(&descriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
	descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	descriptor.nVersion = 1;
	descriptor.dwFlags = PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	descriptor.iPixelType = PFD_TYPE_RGBA;
	descriptor.cColorBits = 24;
	descriptor.cDepthBits = 32;
	descriptor.iLayerType = PFD_MAIN_PLANE;

	HDC hDC = target.impl->dc.GetHandle<HDC>();
	int format = ChoosePixelFormat(hDC, &descriptor);
	if(format == 0)
		Legacy::TryThrowLastError();
	SetPixelFormat(hDC, format, &descriptor);
}

GraphicsContext3D::~GraphicsContext3D() {
	delete impl;
}

void GraphicsContext3D::Resize(Vector2U size) {
	HDC hDC = target.impl->dc.GetHandle<HDC>();
	impl->hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, impl->hRC);
	glViewport(0, 0, size[0], size[1]);
}

void GraphicsContext3D::SetPerspective(float perspective) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble aspect = (GLdouble)(
		target.impl->size[0] / target.impl->size[1]
	);
	gluPerspective(perspective, aspect, .1, 1e2);
	glMatrixMode(GL_MODELVIEW);
}
