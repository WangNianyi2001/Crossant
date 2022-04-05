#pragma once

#include "../graphics.hpp"

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "Msimg32.lib")

namespace Graphics {
	namespace Win32 {
		class OpenGLContext : public Context<HDC> {
		protected:
			GLdouble width, height;
			GLdouble perspective;
			HDC hDC;	// External target drawing context
			HGLRC hRC;
			void FreeRC();
		public:
			virtual ~OpenGLContext();
			virtual void SetTarget(HDC const &target) override;
			virtual void Render() override = 0;
			virtual void SetSize(int width, int height) override;
			void SetPerspective(GLdouble perspective);
		};
	};
}
