#ifndef CHANNEL_MODE_HPP
#define CHANNEL_MODE_HPP

#include "Mode.hpp"
#include <map>

class ChannelMode: public Mode {
public:
	enum ModeList {
		CMODE_O = 1,
		CMODE_S = 4,
		CMODE_I = 8,
		CMODE_T = 16,
		CMODE_N = 32,
		CMODE_L = 128
	};

	ChannelMode(void);
	virtual ~ChannelMode(void);
	virtual std::string	getStrModes(void) const;

	static std::map<char, uint8_t> modesMap;
};

#endif