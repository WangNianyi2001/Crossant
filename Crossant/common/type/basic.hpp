#pragma once

#include <xstring>

namespace Crossant {
	using Byte = unsigned __int8;
	using Float = float;
#ifdef UNICODE
	using Char = wchar_t;
#else
	using Char = char;
#endif
	using String = std::basic_string<Char>;

	constexpr Float PI = 3.14159265359f;
}