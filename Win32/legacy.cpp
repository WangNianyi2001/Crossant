#include "legacy.hpp"
#include "Crossant/common/type.hpp"
#include <Windows.h>

using namespace Crossant::Legacy;

void Crossant::Legacy::TryThrowLastError() {
	int code = GetLastError();
	if(code == 0)
		return;
	throw code;
}

void Crossant::Legacy::ResolveLastError() {
	SetLastError(0);
}
