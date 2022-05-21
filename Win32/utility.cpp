#include "utility.hpp"

void Crossant::TryThrowLastError() {
	int code = GetLastError();
	if(code == 0)
		return;
	throw code;
}