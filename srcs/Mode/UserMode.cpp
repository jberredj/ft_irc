#include "UserMode.hpp"

std::map<char, uint8_t> UserMode::modesMap;

UserMode::UserMode(void): Mode() {
    #ifndef UMODESMAP
        #define UMODESMAP
        UserMode::modesMap.insert(std::make_pair('i', UserMode::UMODE_I));
        UserMode::modesMap.insert(std::make_pair('w', UserMode::UMODE_W));
        UserMode::modesMap.insert(std::make_pair('s', UserMode::UMODE_S));
        UserMode::modesMap.insert(std::make_pair('o', UserMode::UMODE_O));
    #endif
}
UserMode::~UserMode(void) {}

std::string	UserMode::getStrModes(void) const {
    std::string result = "";
    if (hasMode(UMODE_I)) result += "i";
    if (hasMode(UMODE_W)) result += "w";
    if (hasMode(UMODE_S)) result += "s";
    if (hasMode(UMODE_O)) result += "o";
    return result;
}
