#include "context3d.hpp"

using namespace Graphics;

GraphicsContext3D::GraphicsContext3D(Vector2U size) {
	impl = new Impl{};
	impl->bitmap = new Legacy::Bitmap(size);

	PIXELFORMATDESCRIPTOR descriptor;
	memset(&descriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
	descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	descriptor.nVersion = 1;
	descriptor.dwFlags = PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	descriptor.iPixelType = PFD_TYPE_RGBA;
	descriptor.cColorBits = 24;
	descriptor.cDepthBits = 32;
	descriptor.iLayerType = PFD_MAIN_PLANE;

	HDC hDC = impl->bitmap->dc->GetHandle<HDC>();
	int format = ChoosePixelFormat(hDC, &descriptor);
	if(format == 0)
		Legacy::TryThrowLastError();
	SetPixelFormat(hDC, format, &descriptor);
}

GraphicsContext3D::~GraphicsContext3D() {
	delete impl->bitmap;
	delete impl;
}

void GraphicsContext3D::Resize(Vector2U size) {
	HDC hDC = impl->bitmap->dc->GetHandle<HDC>();
	impl->hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, impl->hRC);
	glViewport(0, 0, size[0], size[1]);
}

void GraphicsContext3D::SetPerspective(float perspective) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble aspect = (GLdouble)(
		impl->bitmap->size[0] / impl->bitmap->size[1]
	);
	gluPerspective(perspective, aspect, .1, 1e2);
	glMatrixMode(GL_MODELVIEW);
}
