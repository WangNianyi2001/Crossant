#include "drawer.h"
#include "mydrawer.h"

Drawer *drawer;
int width = 800, height = 600;

bool MainLoop() {
	for(MSG msg; PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE); ) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if(msg.message == WM_QUIT)
			return false;
	}
	drawer->Render();
	return true;
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
	case WM_CREATE:
		drawer->SetHDC(GetDC(hWnd));
		drawer->SetPerspective(45);
		break;
	case WM_KEYUP:
		if(wParam != VK_ESCAPE)
			break;
	case WM_CLOSE:
		delete drawer;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		height = HIWORD(lParam);
		width = LOWORD(lParam);
		drawer->SetSize(width, height);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int nX = (w - width) / 2, nY = (h - height) / 2;

	auto window_class_name = TEXT("Window");
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		window_class_name, NULL
	};
	RegisterClassEx(&wc);
	drawer = new MyDrawer();
	HWND hWnd = CreateWindowEx(NULL,
		window_class_name,
		TEXT("OpenGL Window"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		nX, nY, width, height,
		NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	for(; MainLoop(); );
	return 0;
}
