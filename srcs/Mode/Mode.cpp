#include "Mode.hpp"

Mode::Mode(void): _modes(0) {}

Mode::~Mode(void) {}

void Mode::addMode(uint8_t mode) {
    _modes |= mode;
}

void Mode::removeMode(uint8_t mode) {
    _modes &= ~mode;
}

uint8_t Mode::getModes(void) const {
    return _modes;
}

bool Mode::hasMode(uint8_t mode) const {
    return (_modes & mode);
}
