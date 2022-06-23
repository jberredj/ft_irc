#include "UserMode.hpp"

UserMode::UserMode(void): Mode() {}
UserMode::~UserMode(void) {}

std::string	UserMode::getStrModes(void) const {
    std::string result = "";
    if (hasMode(UMODE_I)) result += "i";
    if (hasMode(UMODE_W)) result += "w";
    if (hasMode(UMODE_S)) result += "s";
    if (hasMode(UMODE_O)) result += "o";
    return result;
}
