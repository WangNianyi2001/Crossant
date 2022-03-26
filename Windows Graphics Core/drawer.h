#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <gl/gl.h>
#include <gl/glu.h>

class Drawer {
public:
	struct Color3f { GLfloat r, g, b; };
protected:
	int width = 800, height = 600;
	double perspective;
	Color3f clear_color{ 0, 0, 0 };
public:
	HDC hDC;
	HGLRC hRC;

	virtual ~Drawer() {
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
	}

	void SetSize(int width, int height) {
		this->width = width;
		this->height = height;
		glViewport(0, 0, width, height);
		SetPerspective(perspective);
	}

	void SetPerspective(double perspective) {
		this->perspective = perspective;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		GLdouble aspect = (GLdouble)width / height;
		gluPerspective(perspective, aspect, .1, 1e2);
		glMatrixMode(GL_MODELVIEW);
	}

	void SetClearColor(Color3f color) {
		clear_color = color;
		glClearColor(color.r, color.g, color.b, 1);
	}

	void SetHDC(HDC hDC) {
		this->hDC = hDC;
		SetupPixelFormat();
	}

	bool SetupPixelFormat() {
		PIXELFORMATDESCRIPTOR descriptor;
		memset(&descriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
		descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		descriptor.iPixelType = PFD_TYPE_RGBA;
		descriptor.cDepthBits = 32;
		descriptor.iLayerType = PFD_MAIN_PLANE;
		int pixel_format = ChoosePixelFormat(hDC, &descriptor);
		if(!pixel_format) {
			MessageBox(NULL, TEXT("No proper display mode"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}
		SetPixelFormat(hDC, pixel_format, &descriptor);
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		return true;
	}

	virtual void PostUpdate() {}

	void Render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glPushMatrix();
		Draw();
		glPopMatrix();
		glFlush();
		SwapBuffers(hDC);
		PostUpdate();
	}

	virtual void Draw() {}
};
