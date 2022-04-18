#pragma once

#include "../../drawingcontext.hpp"

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

namespace Graphics::Win32 {
	class OpenGLContext : public DrawingContext<HDC> {
	protected:
		GLdouble width, height;
		GLdouble perspective;
		HDC target;
		HGLRC hRC;
		virtual void Dispose() override;
	public:
		virtual ~OpenGLContext() override;
		virtual void SetTarget(HDC const &target) override;
		virtual void Render() override = 0;
		virtual void SetSize(int width, int height) override;
		void SetPerspective(GLdouble perspective);
	};
}
