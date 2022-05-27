#include "Crossant/crossant.hpp"
#include <sstream>
#include <Windows.h>

Crossant::String Crossant::ChooseFile(
	std::map<String, std::set<String>> restrictions
) {
	OPENFILENAME ofn;
	Char szFile[260] = TEXT("");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	std::basic_stringstream<Char, std::char_traits<Char>, std::allocator<Char>> filterSs;
	for(auto restriction : restrictions) {
		auto &types = restriction.second;
		if(types.size() == 0)
			continue;
		filterSs << restriction.first << '\0';
		filterSs << *types.begin();
		for(auto it = ++types.begin(); it != types.end(); ++it)
			filterSs << ';' << *it;
		filterSs << '\0';
	}
	String filter;
	filterSs >> filter;
	ofn.lpstrFilter = filter.c_str();
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	if(!GetOpenFileName(&ofn))
		return String{};
	return szFile;
}