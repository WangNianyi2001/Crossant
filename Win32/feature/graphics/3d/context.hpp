#pragma once

#pragma comment(lib, "OpenGL32.Lib")
#pragma comment(lib, "GlU32.Lib")

#include "Crossant/feature/graphics/3d/context.hpp"
#include <Windows.h>
#include "gl/gl.h"
#include "gl/glu.h"

#ifdef CreateWindow
#pragma push_macro("CreateWindow")
#undef CreateWindow
#endif

namespace Crossant::Graphics::Graphics3D {
	struct Context::Impl {
		HDC hDC = NULL;
		HGLRC hRC = NULL;
	};
}
