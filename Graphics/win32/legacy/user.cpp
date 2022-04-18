#include "user.hpp"
#include <Windows.h>

#define GET_HANDLE(type, obj) (\
	obj == nullptr ? NULL :\
	reinterpret_cast<type>((obj)->handle)\
)

using namespace Graphics::Win32::Legacy;

ATOM RegisterClass(WindowClass::Info info) {
	WNDCLASSEX classEx;
	classEx.cbSize = sizeof(WNDCLASSEX);
	classEx.style = (UINT)info.style;
	classEx.lpfnWndProc = (WNDPROC)info.process;
	classEx.cbClsExtra = 0;
	classEx.cbWndExtra = 0;
	classEx.hInstance = info.instance->GetHandle<HINSTANCE>();
	classEx.hIcon = info.icon->GetHandle<HICON>();
	classEx.hCursor = info.cursor->GetHandle<HCURSOR>();
	classEx.hbrBackground = info.brush->GetHandle<HBRUSH>();
	classEx.lpszMenuName = info.menuName.c_str();
	classEx.lpszClassName = info.className.c_str();
	classEx.hIconSm = info.smallIcon->GetHandle<HICON>();
	ATOM classId = RegisterClassEx(&classEx);
	if(!classId)
		TryThrowLastError();
	return classId;
}

WindowClass::WindowClass(Info info) : info(info), id(RegisterClass(info)) {}

WindowClass::~WindowClass() {
	if(!UnregisterClass((LPCWSTR)id, info.instance->GetHandle<HINSTANCE>()))
		TryThrowLastError();
}

