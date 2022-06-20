#ifndef MODE_HPP
#define MODE_HPP

#include "stdint.h"

class Mode {
public:

    Mode(void);
    ~Mode(void);

    void addMode(uint8_t mode);
    void removeMode(uint8_t mode);
    uint8_t getModes(void) const;
    bool hasMode(uint8_t mode) const;

private:
    uint8_t _modes;

};

#endif