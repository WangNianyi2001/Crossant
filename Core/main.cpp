#include "graphics/win32/bitmap.hpp"
#include <vector>

using namespace Graphics::Win32;

struct Vec2 {
	float x, y;
	float mod() {
		return sqrtf(x * x + y * y);
	}
	Vec2 operator+(Vec2 pos) {
		return Vec2{ x + pos.x, y + pos.y };
	}
	Vec2 operator*(float scale) {
		return Vec2{ x * scale, y * scale };
	}
	Vec2 operator-(Vec2 pos) {
		return operator+(pos * -1);
	}
	Vec2 unify() {
		return operator*(1 / mod());
	}
};

struct Line {
	Vec2 begin, end;
	Vec2 vec() {
		return end - begin;
	}
	float len() {
		return vec().mod();
	}
};

class DrawingContext : public BitmapContext {
	static constexpr inline BLENDFUNCTION blend_function = {
		AC_SRC_OVER, 0, 255, AC_SRC_ALPHA
	};
public:
	void DrawPixel(Vec2 pos) {
		Rectangle(hDC, pos.x, pos.y, pos.x + 2, pos.y + 2);
		int a = GetLastError();
	}

	void DrawLine(Line line) {
		HGDIOBJ old_brush = SelectObject(hDC, GetStockObject(WHITE_BRUSH));
		HGDIOBJ old_pen = SelectObject(hDC, GetStockObject(NULL_PEN));
		float len = line.len();
		int step_count = ceilf(len);
		float unit_len = len / step_count;
		Vec2 unit = line.vec().unify() * unit_len;
		for(int i = 0; i < step_count; ++i) {
			Vec2 pos = line.begin + unit * i;
			DrawPixel(pos);
		}
		DrawPixel(line.end);
		SelectObject(hDC, old_brush);
		SelectObject(hDC, old_pen);
	}

	virtual void Render() override {
		//AlphaBlend(target, 0, 0, width, height, hDC, 0, 0, width, height, blend_function);
		BitBlt(target, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
	}
};

DrawingContext *context;
bool first = false;
Vec2 mouse_pos, first_point;
std::vector<Line> lines;

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
	case WM_ACTIVATE:
		context->SetTarget(GetDC(hWnd));
		break;
	case WM_PAINT:
		SelectObject(context->hDC, GetStockObject(BLACK_BRUSH));
		Rectangle(context->hDC, 0, 0, context->width, context->height);
		for(Line line : lines)
			context->DrawLine(line);
		if(first)
			context->DrawLine({ first_point, mouse_pos });
		context->Render();
		ValidateRect(hWnd, NULL);
		break;
	case WM_LBUTTONDOWN:
		if(first)
			lines.push_back({ first_point, mouse_pos });
		else
			first_point = mouse_pos;
		first = !first;
		break;
	case WM_MOUSEMOVE:
		mouse_pos = { (float)LOWORD(lParam), (float)HIWORD(lParam) };
		if(first)
			InvalidateRect(hWnd, NULL, false);
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
