#pragma once

#include "Crossant/common/basic.hpp"
#include <map>
#include <set>

namespace Crossant {
	String ChooseFile(
		std::map<String, std::set<String>> restrictions = {}
	);
}