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
	impl->hRC = wglCreateContext(impl->hDC);
	if(!impl->hRC)
		Legacy::TryThrowLastError();
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

void GraphicsContext3D::Flush() {
	glFlush();
}

void GraphicsContext3D::SwapBuffer() {
	SwapBuffers(impl->hDC);
}

using AM = GraphicsContext3D::AttributeMask;
std::map<AM, int> attributeMaskMap{
	{ AM::Current, GL_CURRENT_BIT },
	{ AM::Point, GL_POINT_BIT },
	{ AM::Line, GL_LINE_BIT },
	{ AM::Polygon, GL_POLYGON_BIT },
	{ AM::PolygonStipple, GL_POLYGON_STIPPLE_BIT },
	{ AM::PixelMode, GL_PIXEL_MODE_BIT },
	{ AM::Lighting, GL_LIGHTING_BIT },
	{ AM::Fog, GL_FOG_BIT },
	{ AM::DepthBuffer, GL_DEPTH_BUFFER_BIT },
	{ AM::AccumBuffer, GL_ACCUM_BUFFER_BIT },
	{ AM::StencilBuffer, GL_STENCIL_BUFFER_BIT },
	{ AM::Viewport, GL_VIEWPORT_BIT },
	{ AM::Transform, GL_TRANSFORM_BIT },
	{ AM::Enable, GL_ENABLE_BIT },
	{ AM::ColorBuffer, GL_COLOR_BUFFER_BIT },
	{ AM::Hint, GL_HINT_BIT },
	{ AM::Eval, GL_EVAL_BIT },
	{ AM::List, GL_LIST_BIT },
	{ AM::Texture, GL_TEXTURE_BIT },
	{ AM::Scissor, GL_SCISSOR_BIT }
};
void GraphicsContext3D::Clear(AM attributes) {
	glClear(attributeMaskMap[attributes]);
}

void GraphicsContext3D::SetMatrixMode(MatrixMode mode) {
	glMatrixMode(matrixModeMap[mode]);
}

void GraphicsContext3D::LoadIdentity() {
	glLoadIdentity();
}

void GraphicsContext3D::Translate(Coord3D translation) {
	glTranslatef(translation[0], translation[1], translation[2]);
}

void GraphicsContext3D::Rotate(Float angle, Coord3D axis) {
	glRotatef(angle, axis[0], axis[1], axis[2]);
}

void GraphicsContext3D::Scale(Coord3D scalor) {
	glScalef(scalor[0], scalor[1], scalor[2]);
}

void GraphicsContext3D::SetPerspective(Float perspective) {
	SetMatrixMode(MM::Projection);
	LoadIdentity();
	GLdouble aspect = (GLdouble)target.impl->size[0] / target.impl->size[1];
	gluPerspective(perspective, aspect, .1, 1e2);
	SetMatrixMode(MM::Space);
	glViewport(0, 0, target.impl->size[0], target.impl->size[1]);
}

using GT = GraphicsContext3D::GeometryType;
std::map<GT, int> geometryTypeMap{
	{ GT::Points, GL_POINTS },
	{ GT::Lines, GL_LINES },
	{ GT::LineStrip, GL_LINE_STRIP },
	{ GT::LineLoop, GL_LINE_LOOP },
	{ GT::Triangles, GL_TRIANGLES },
	{ GT::TriangleStrip, GL_TRIANGLE_STRIP },
	{ GT::TriangleFan, GL_TRIANGLE_FAN },
	{ GT::Quads, GL_QUADS },
	{ GT::QuadStrip, GL_QUAD_STRIP },
	{ GT::Polygon, GL_POLYGON }
};
void GraphicsContext3D::Begin(GeometryType type) {
	glBegin(geometryTypeMap[type]);
}

void GraphicsContext3D::End() {
	glEnd();
}

void GraphicsContext3D::Vertex(Coord3D coordinate) {
	glVertex3fv((GLfloat *)&coordinate);
}

void GraphicsContext3D::Color(Graphics::Color color) {
	glColor3fv((GLfloat *)&color);
}