#include "drawingcontext.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

void DrawingContext::Draw() {
	window->BeginPaint();
	Push();
	window->FinishPaint();
}
