#ifndef USER_MODE_HPP
#define USER_MODE_HPP

#include "Mode.hpp"

// Parameters: <nickname> {[+|-]|i|w|s|o}

class UserMode: public Mode {
public:
    enum ModeList {
        UMODE_I = 1,
        UMODE_W = 2,
        UMODE_S = 4,
        UMODE_O = 8,
    };

    UserMode(void);
    virtual ~UserMode(void);
	virtual std::string	getStrModes(void) const;

	static std::map<char, uint8_t> modesMap;
};

#endif