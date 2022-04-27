#pragma once

#pragma comment(lib, "OpenGL32.Lib")
#pragma comment(lib, "GlU32.Lib")

#include "../../win32.hpp"
#include "GL/gl.h"
#include "GL/glu.h"

namespace Graphics {
	struct GraphicsContext3D::Impl {
		Legacy::Bitmap *bitmap;
		HGLRC hRC;
	};
}
