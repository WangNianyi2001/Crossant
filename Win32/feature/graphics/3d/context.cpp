#include "context.hpp"
#include "../target.hpp"
#include "Win32/legacy.hpp"
#include <cmath>

using namespace Crossant::Graphics::Graphics3D;

PIXELFORMATDESCRIPTOR descriptorTemplate{
	.nSize = sizeof(PIXELFORMATDESCRIPTOR),
	.nVersion = 1,
	.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL,
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

Context::Context(Graphics::Target &target) : Graphics::Context(target) {
	impl = new Impl{};
	OnResize();
}

Context::~Context() {
	delete impl;
}

void Context::MakeCurrent() const {
	wglMakeCurrent(impl->hDC, impl->hRC);
	glEnable(GL_DEPTH_TEST);
}

void Context::OnResize() {
	if(impl->hRC) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(impl->hRC);
	}
	PIXELFORMATDESCRIPTOR descriptor = descriptorTemplate;
	impl->hDC = target.impl->dc.GetHandle<HDC>();
	int format = ChoosePixelFormat(impl->hDC, &descriptor);
	if(format == 0)
		Legacy::TryThrowLastError();
	else
		Legacy::ResolveLastError();
	SetPixelFormat(impl->hDC, format, &descriptor);
	impl->hRC = wglCreateContext(impl->hDC);
	if(!impl->hRC)
		Legacy::TryThrowLastError();
	MakeCurrent();
	auto size = target.Size();
	glViewport(0, 0, size[0], size[1]);
	SetPerspective(impl->perspective);
}

using MM = Context::MatrixMode;
std::map<MM, int> matrixModeMap{
	{ MM::Projection, GL_PROJECTION },
	{ MM::Space, GL_MODELVIEW },
	{ MM::Texture, GL_TEXTURE },
};

void Context::Finish() {
	glFinish();
}

using AM = Context::AttributeMask;
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

void Context::Clear(std::initializer_list<AM> attributes) {
	int mask = 0;
	for(AM attribute : attributes)
		mask |= attributeMaskMap[attribute];
	glClear(mask);
}

void Context::SetMatrixMode(MatrixMode mode) {
	glMatrixMode(matrixModeMap[mode]);
}

void Context::LoadIdentity() {
	glLoadIdentity();
}

void Context::Translate(Coord3D const &translation) {
	glTranslatef(translation[0], translation[1], translation[2]);
}

void Context::Rotate(Float angle, Coord3D const &axis) {
	angle *= 180.f / PI;
	glRotatef(angle, axis[0], axis[1], axis[2]);
}

void Context::Rotate(Quaternion const &quaternion) {
	Float const angle = std::atan2(quaternion.im.Module(), quaternion.re) * 2;
	if(std::abs(angle) < 1e-3f)
		return;
	Rotate(angle, quaternion.im);
}

void Context::Scale(Coord3D const &scalor) {
	glScalef(scalor[0], scalor[1], scalor[2]);
}

void Context::SetPerspective(Float perspective) {
	impl->perspective = perspective;
	SetMatrixMode(MM::Projection);
	LoadIdentity();
	auto &size = target.impl->size;
	GLdouble aspect = (GLdouble)size[0] / size[1];
	gluPerspective(perspective, aspect, .1, 1e2);
	SetMatrixMode(MM::Space);
}

using DUT = Context::DatumType;
std::map<DUT, int> datumTypeMap{
	{ DUT::Byte, GL_BYTE },
	{ DUT::UnsignedByte, GL_UNSIGNED_BYTE },
	{ DUT::Short, GL_SHORT },
	{ DUT::UnsignedShort, GL_UNSIGNED_SHORT },
	{ DUT::Int, GL_INT },
	{ DUT::UnsignedInt, GL_UNSIGNED_INT },
	{ DUT::Float, GL_FLOAT },
	{ DUT::Double, GL_DOUBLE },
	{ DUT::Byte2, GL_2_BYTES },
	{ DUT::Byte3, GL_3_BYTES },
	{ DUT::Byte4, GL_4_BYTES },
};

using DT = Context::DataType;
std::map<DT, int> dataTypeMap{
	{ DT::Color, GL_COLOR_ARRAY },
	{ DT::EdgeFlag, GL_EDGE_FLAG_ARRAY },
	{ DT::Normal, GL_NORMAL_ARRAY },
	{ DT::TexCoord, GL_TEXTURE_COORD_ARRAY },
	{ DT::Vertex, GL_VERTEX_ARRAY }
};

void Context::SetDataArrayState(DT type, bool enabled) {
	int cap = dataTypeMap[type];
	if(enabled)
		glEnableClientState(cap);
	else
		glDisableClientState(cap);
}

void Context::SetDataArray(DT type, void const *data, unsigned stride, DUT datumType, int dimension) {
	int dut = datumTypeMap[datumType];
	switch(type) {
	case DT::Color:
		glColorPointer(dimension, dut, stride, data);
		break;
	case DT::EdgeFlag:
		glEdgeFlagPointer(stride, data);
		break;
	case DT::Normal:
		glNormalPointer(dut, stride, data);
		break;
	case DT::TexCoord:
		glTexCoordPointer(dimension, dut, stride, data);
		break;
	case DT::Vertex:
		glVertexPointer(dimension, dut, stride, data);
		break;
	}
}

using GT = Context::GeometryType;
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

void Context::DrawElements(GT type, unsigned count, unsigned const *indices, DUT datumType) {
	glDrawElements(geometryTypeMap[type], count, datumTypeMap[datumType], indices);
}

using FT = Context::FaceType;
using FM = Context::FaceMode;

std::map<FT, int> faceTypeMap{
	{ FT::Front, GL_FRONT },
	{ FT::Back, GL_BACK },
	{ FT::Both, GL_FRONT_AND_BACK },
};

std::map<FM, int> faceModeMap{
	{ FM::Point, GL_POINT },
	{ FM::Line, GL_LINE },
	{ FM::Fill, GL_FILL },
};

void Context::PolygonMode(FaceType type, FaceMode mode) {
	glPolygonMode(faceTypeMap[type], faceModeMap[mode]);
}