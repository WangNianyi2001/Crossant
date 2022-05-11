#include "gdi.hpp"
#include <Windows.h>

using namespace Crossant::Legacy;

PaintStruct::PaintStruct() : ps(new PAINTSTRUCT) {}

PaintStruct::~PaintStruct() {
	delete ps;
}

