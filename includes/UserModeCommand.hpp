#ifndef USER_MODE_COMMAND_HPP
#define USER_MODE_COMMAND_HPP

#include <string>
#include "User.hpp"
#include "Command.hpp"

class UserModeCommand {
private:
	std::string _modeChanges;
	std::string	_request;
	Command	&_command;
	User	&_invoker;
	bool	_addSign;
	uint8_t	_mode;
	char	_chrMode;

	void	_addMode(void);
	void	_removeMode(void);

public:
	UserModeCommand(Command &command);
	void    updateModes(void);
};

#endif
