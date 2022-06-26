#include "UserMode.hpp"

std::map<char, uint8_t> UserMode::modesMap;

UserMode::UserMode(void): Mode() {
	if (modesMap.empty()) {
		modesMap.insert(std::make_pair('i', UMODE_I));
		modesMap.insert(std::make_pair('w', UMODE_W));
		modesMap.insert(std::make_pair('s', UMODE_S));
		modesMap.insert(std::make_pair('o', UMODE_O));
	}
}

UserMode::~UserMode(void) {}

std::string	UserMode::getStrModes(void) const { // TODO : refactor this to use modesmap
	std::string result = "";
	for (std::map<char, uint8_t>::iterator mode = modesMap.begin(); mode != modesMap.end(); mode++) {
		if (hasMode(mode->second))
			result += mode->first;
	}
	return result;
}
