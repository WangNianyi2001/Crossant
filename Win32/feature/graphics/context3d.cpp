#include "context3d.hpp"

using namespace Graphics;

PIXELFORMATDESCRIPTOR descriptorTemplate{
	.nSize = sizeof(PIXELFORMATDESCRIPTOR),
	.nVersion = 1,
	.dwFlags = PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	.iPixelType = PFD_TYPE_RGBA,
	.cColorBits = 24,
	.cRedBits = 0,
	.cRedShift = 0,
	.cGreenBits = 0,
	.cGreenShift = 0,
	.cBlueBits = 0,
	.cBlueShift = 0,
	.cAlphaBits = 0,
	.cAccumBits = 0,
	.cAccumRedBits = 0,
	.cAccumGreenBits = 0,
	.cAccumBlueBits = 0,
	.cAccumAlphaBits = 0,
	.cDepthBits = 32,
	.cStencilBits = 0,
	.cAuxBuffers = 0,
	.iLayerType = PFD_MAIN_PLANE,
	.bReserved = 0,
	.dwLayerMask = 0,
	.dwVisibleMask = 0,
	.dwDamageMask = 0
};

GraphicsContext3D::GraphicsContext3D(GraphicsTarget &target) : GraphicsContext(target) {
	impl = new Impl{};

	PIXELFORMATDESCRIPTOR descriptor = descriptorTemplate;
	impl->hDC = target.impl->dc.GetHandle<HDC>();
	int format = ChoosePixelFormat(impl->hDC, &descriptor);
	if(format == 0)
		Legacy::TryThrowLastError();
	SetPixelFormat(impl->hDC, format, &descriptor);
}

GraphicsContext3D::~GraphicsContext3D() {
	delete impl;
}

void GraphicsContext3D::MakeCurrent() const {
	wglMakeCurrent(impl->hDC, impl->hRC);
}

void GraphicsContext3D::Resize(Size2D size) {
	target.Resize(size);
	impl->hRC = wglCreateContext(impl->hDC);
	glViewport(0, 0, size[0], size[1]);
}

using MM = GraphicsContext3D::MatrixMode;
std::map<MM, int> matrixModeMap{
	{ MM::Projection, GL_PROJECTION },
	{ MM::Space, GL_MODELVIEW },
	{ MM::Texture, GL_TEXTURE },
};

inline void GraphicsContext3D::SetMatrixMode(MatrixMode mode) {
	glMatrixMode(matrixModeMap[mode]);
}

inline void GraphicsContext3D::LoadIdentity() {
	glLoadIdentity();
}

inline void GraphicsContext3D::Translate(Coord3D translation) {
	glTranslatef(translation[0], translation[1], translation[2]);
}

inline void GraphicsContext3D::Rotate(Float angle, Coord3D axis) {
	glRotatef(angle, axis[0], axis[1], axis[2]);
}

inline void GraphicsContext3D::Scale(Coord3D scalor) {
	glScalef(scalor[0], scalor[1], scalor[2]);
}

void GraphicsContext3D::SetPerspective(Float perspective) {
	SetMatrixMode(MM::Projection);
	LoadIdentity();
	GLdouble aspect = (GLdouble)target.impl->size[0] / target.impl->size[1];
	gluPerspective(perspective, aspect, .1, 1e2);
}
