#include "ChannelMode.hpp"

ChannelMode::ChannelMode(void): Mode() {}
ChannelMode::~ChannelMode(void) {}

std::string	ChannelMode::getStrModes(void) const {
    std::string result = "";
    if (hasMode(CMODE_O)) result += "o";
    if (hasMode(CMODE_P)) result += "p";
    if (hasMode(CMODE_S)) result += "s";
    if (hasMode(CMODE_I)) result += "i";
    if (hasMode(CMODE_T)) result += "t";
    if (hasMode(CMODE_N)) result += "n";
    if (hasMode(CMODE_B)) result += "b";
    if (hasMode(CMODE_V)) result += "v";
    return result;
}
