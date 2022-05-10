#pragma once

#pragma comment(lib, "OpenGL32.Lib")
#pragma comment(lib, "GlU32.Lib")

#include "Graphics/feature/graphics/context3d.hpp"
#include <Windows.h>
#include "gl/gl.h"
#include "gl/glu.h"

namespace Graphics {
	struct GraphicsContext3D::Impl {
		HDC hDC;
		HGLRC hRC;
		float perspective = 1;
	};
}
