#include "legacy.hpp"
#include "Graphics/common/type.hpp"
#include <Windows.h>

using namespace Graphics::Legacy;

void Graphics::Legacy::TryThrowLastError() {
	int code = GetLastError();
	if(code == 0)
		return;
	throw code;
}

void Graphics::Legacy::ResolveLastError() {
	SetLastError(0);
}