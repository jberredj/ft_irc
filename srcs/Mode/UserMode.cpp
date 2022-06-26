#include "UserMode.hpp"

std::map<char, uint8_t> UserMode::modesMap;

UserMode::UserMode(void): Mode() {
	if (UserMode::modesMap.empty()) {
		UserMode::modesMap.insert(std::make_pair('i', UserMode::UMODE_I));
		UserMode::modesMap.insert(std::make_pair('w', UserMode::UMODE_W));
		UserMode::modesMap.insert(std::make_pair('s', UserMode::UMODE_S));
		UserMode::modesMap.insert(std::make_pair('o', UserMode::UMODE_O));
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
