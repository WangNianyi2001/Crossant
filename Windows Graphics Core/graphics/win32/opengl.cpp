#include "opengl.hpp"

using namespace Graphics::Win32;

void OpenGLContext::FreeRC() {
	if(hRC == NULL)
		return;
	wglDeleteContext(hRC);
	hRC = NULL;
}

OpenGLContext::~OpenGLContext() {
	FreeRC();
}

void OpenGLContext::SetTarget(HDC const &target) {
	hDC = target;
	FreeRC();
	PIXELFORMATDESCRIPTOR descriptor;
	memset(&descriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
	descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	descriptor.iPixelType = PFD_TYPE_RGBA;
	descriptor.cDepthBits = 32;
	descriptor.iLayerType = PFD_MAIN_PLANE;
	int index = ChoosePixelFormat(hDC, &descriptor);
	if(!index) {
		MessageBox(NULL, TEXT("No proper display mode"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		throw GetLastError();
	}
	SetPixelFormat(hDC, index, &descriptor);
}

void OpenGLContext::SetSize(int width, int height) {
	this->width = width;
	this->height = height;
	FreeRC();
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	glViewport(0, 0, width, height);
	SetPerspective(perspective);
}

void OpenGLContext::SetPerspective(GLdouble perspective) {
	this->perspective = perspective;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble aspect = (GLdouble)width / height;
	gluPerspective(perspective, aspect, .1, 1e2);
	glMatrixMode(GL_MODELVIEW);
}
