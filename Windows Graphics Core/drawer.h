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
#include <gl/glut.h>

class Drawer {
public:
	struct Color3f { GLclampf r, g, b; };
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
		descriptor.cColorBits = 32;
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

		// Enable lighting
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 50.0 };
		GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_SMOOTH);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		return true;
	}

	virtual void PostUpdate() {}

	void Render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(clear_color.r, clear_color.g, clear_color.b, 1);
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
