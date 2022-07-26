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

std::string	UserMode::getStrModes(void) const {
	std::string result = "";
	for (std::map<char, uint8_t>::iterator pair = modesMap.begin(); pair != modesMap.end(); pair++) {
		if (hasMode(pair->second))
			result += pair->first;
	}
	return result;
}
