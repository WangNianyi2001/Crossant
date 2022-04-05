#include "graphics/win32/bitmap.hpp"

using namespace Graphics::Win32;

class DrawingContext : public BitmapContext {
	static constexpr inline BLENDFUNCTION blend_function = {
		AC_SRC_OVER, 0, 255, AC_SRC_ALPHA
	};
public:
	virtual void Render() override {
		SelectObject(hDC, GetStockObject(BLACK_BRUSH));
		Rectangle(hDC, 0, 0, width, height);
		SelectObject(hDC, GetStockObject(WHITE_BRUSH));
		Ellipse(hDC, 0, 0, 100, 200);
		//AlphaBlend(target, 0, 0, width, height, hDC, 0, 0, width, height, blend_function);
		BitBlt(target, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
	}
};

BitmapContext *context;

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
	case WM_ACTIVATE:
		context->SetTarget(GetDC(hWnd));
		break;
	case WM_PAINT:
		context->Render();
		break;
	case WM_DESTROY:
		delete context;
		PostQuitMessage(0);
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
