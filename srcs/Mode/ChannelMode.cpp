#include "ChannelMode.hpp"

std::map<char, uint8_t> ChannelMode::modesMap;

ChannelMode::ChannelMode(void): Mode() {
	if (modesMap.empty()) {
		modesMap.insert(std::make_pair('o', CMODE_O));
		// modesMap.insert(std::make_pair('p', CMODE_P));
		modesMap.insert(std::make_pair('s', CMODE_S));
		modesMap.insert(std::make_pair('i', CMODE_I));
		modesMap.insert(std::make_pair('t', CMODE_T));
		modesMap.insert(std::make_pair('n', CMODE_N));
		modesMap.insert(std::make_pair('b', CMODE_B));
		modesMap.insert(std::make_pair('l', CMODE_L));
	}
}

ChannelMode::~ChannelMode(void) {}

std::string	ChannelMode::getStrModes(void) const {
	std::string result = "";
	for (std::map<char, uint8_t>::iterator pair = modesMap.begin(); pair != modesMap.end(); pair++) {
		if (hasMode(pair->second))
			result += pair->first;
	}
	return result;
}
