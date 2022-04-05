#include "graphics/win32/opengl.hpp"
#include <gl/glut.h>

using namespace Graphics::Win32;

class DrawingContext : public OpenGLContext {
public:
	virtual void Render() override {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(0, 0, -4);
		//
		glutSolidSphere(1, 8, 8);
		//
		glPopMatrix();
		glFlush();
		SwapBuffers(hDC);
	}
};

OpenGLContext *context;

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
	case WM_ACTIVATE:
		context->SetTarget(GetDC(hWnd));
		context->SetPerspective(45);
		break;
	case WM_PAINT: {
		context->Render();
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_QUIT:
		delete context;
		break;
	case WM_SIZE:
		context->SetSize(LOWORD(lParam), HIWORD(lParam));
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	int iw = 800, ih = 600;
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int nX = (w - iw) / 2, nY = (h - ih) / 2;

	auto window_class_name = TEXT("Window");
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		window_class_name, NULL
	};
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindowEx(NULL,
		window_class_name,
		TEXT("OpenGL Window"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		nX, nY, iw, ih,
		NULL, NULL, hInst, NULL);

	context = new DrawingContext();

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	for(MSG msg; ; ) {
		if(!PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			continue;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if(msg.message == WM_QUIT)
			break;
	}

	return 0;
}
