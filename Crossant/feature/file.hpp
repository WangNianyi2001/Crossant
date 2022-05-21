#pragma once

#include "Crossant/common/basic.hpp"
#include <fstream>
#include <map>
#include <set>

namespace Crossant {
	struct File : std::fstream {
		static File ChooseFromDisk(
			std::map<String, std::set<String>> restrictions = {}
		);

		File() = default;

		File(String path) : std::fstream(path) {}
	};
}