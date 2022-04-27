#pragma once

#include "../../win32.hpp"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

namespace Graphics {
	struct GraphicsContext3D::Impl {
		Legacy::Bitmap *bitmap;
		HGLRC hRC;
	};
}
