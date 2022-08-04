#ifndef CHANNEL_MODE_HPP
#define CHANNEL_MODE_HPP

#include "Mode.hpp"
#include <map>
//    Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]

class ChannelMode: public Mode {
public:
	enum ModeList {
		CMODE_O = 1, // give/take channel operator privilege; - TODO
		// CMODE_P = 2, // private channel (deprecated) - NOT DO
		CMODE_S = 4, // secret channel
		CMODE_I = 8, // invite-only channel - TODO
		CMODE_T = 16, // topic settable by channel operator only flag; TODO
		CMODE_N = 32, // no messages to channel from clients on the outside; TODO
		CMODE_B = 64, // set/remove a ban mask to keep users out; (1459)
		CMODE_L = 128 // set/remove the user limit to channel; (1459) // DO NOT USE THIS FLAG LIKE A SET/UNSET VALUE
		// CMODE_V = 128 // give/take the voice privilege; (2811) - give/take the ability to speak on a moderated channel; (1459) - TODO ? Nobody does it 
		// K . // set/remove a channel key (password).(1459)
		// M // moderated channel; (1459)
	};

	ChannelMode(void);
	virtual ~ChannelMode(void);
	virtual std::string	getStrModes(void) const;

	static std::map<char, uint8_t> modesMap;
};

#endif