#ifndef USER_MODE_COMMAND_HPP
#define USER_MODE_COMMAND_HPP

#include <string>
#include "User.hpp"
#include "Command.hpp"

class UserModeCommand {
public:
	UserModeCommand(Command &command);
	void	updateModes(void);

private:
	Command	&_command;
	User	&_invoker;
	std::string _modeChanges;
	std::string	_request;
	bool	_addSign;
	bool	_oldSign;
	bool	_firstSign;
	uint8_t	_mode;
	char	_chrMode;

	void	_retrieveTargetModes(void);
	void	_addMode(void);
	void	_removeMode(void);
	void	_updateSign(void);
	void	_sendReply(void);

};

#endif
