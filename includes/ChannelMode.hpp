#ifndef CHANNEL_MODE_HPP
#define CHANNEL_MODE_HPP

#include "Mode.hpp"
#include <map>
//    Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]

class ChannelMode: public Mode {
public:
	enum ModeList {
		CMODE_O = 1, // TODO .
		// CMODE_P = 2, // TO REMOVE
		CMODE_S = 4,
		CMODE_I = 8, // TODO .
		CMODE_T = 16, // TODO
		CMODE_N = 32, // 
		CMODE_B = 64, // not to do
		CMODE_V = 128
		// L . 
		// K .
	};

	ChannelMode(void);
	virtual ~ChannelMode(void);
	virtual std::string	getStrModes(void) const;

	static std::map<char, uint8_t> modesMap;
};

#endif