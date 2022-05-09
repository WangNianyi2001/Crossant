#pragma once

#pragma comment(lib, "OpenGL32.Lib")
#pragma comment(lib, "GlU32.Lib")

#include "../../win32.hpp"
#include "gl/gl.h"
#include "gl/glu.h"

namespace Graphics {
	struct GraphicsContext3D::Impl {
		HDC hDC;
		HGLRC hRC;
	};
}
