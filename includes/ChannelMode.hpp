#ifndef CHANNEL_MODE_HPP
#define CHANNEL_MODE_HPP

#include "Mode.hpp"

//    Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]

class ChannelMode: public Mode {
public:
    enum ModeList {
        CMODE_O = 1,
        CMODE_P = 2,
        CMODE_S = 4,
        CMODE_I = 8,
        CMODE_T = 16,
        CMODE_N = 32,
        CMODE_B = 64,
        CMODE_V = 128
    };

    ChannelMode(void);
    virtual ~ChannelMode(void);
};

#endif