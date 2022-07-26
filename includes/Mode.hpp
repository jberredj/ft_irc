#ifndef MODE_HPP
#define MODE_HPP

#include "stdint.h"
#include <string>
#include <map>

class Mode {
public:

	Mode(void);
	virtual ~Mode(void);

	void	addMode(uint8_t mode);
	void	removeMode(uint8_t mode);
	uint8_t	getModes(void) const;
	bool	hasMode(uint8_t mode) const;
	virtual std::string	getStrModes(void) const = 0;

private:
	uint8_t _modes;

};

#endif