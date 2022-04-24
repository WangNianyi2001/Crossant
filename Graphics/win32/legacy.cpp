#include "legacy.hpp"
#include "../common/type.hpp"
#include <Windows.h>

using namespace Graphics::Win32::Legacy;

void Graphics::Win32::Legacy::TryThrowLastError() {
	int code = GetLastError();
	if(code == 0)
		return;
	SetLastError(0);
	Char *buffer = nullptr;
	size_t size = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&buffer, 0, NULL);
	String msg(buffer, size);
	LocalFree(buffer);
	throw msg;
}
