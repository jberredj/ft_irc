#ifndef CHANNEL_MODE_COMMAND_HPP
#define CHANNEL_MODE_COMMAND_HPP

#include <string>
#include "User.hpp"
#include "Command.hpp"
#include "helpers.hpp"

class ChannelModeCommand {
public:
	ChannelModeCommand(Command &command);
	void	updateModes(void);

private:
	Command	&_command;
	Channel	*_channel;
	std::string _modeChanges;
	std::string	_request;
	bool	_addSign;
	bool	_oldSign;
	bool	_firstSign;
	uint8_t	_mode;
	char	_chrMode;
	int		_currentParamIdx;
	std::string _currentParam;


	void	_retrieveChannelModes(void);
	void	_addMode(void);
	void	_removeMode(void);
	void	_updateSign(void);
	void	_rplChannelmodeis();
	void	_rplCreationTime(Channel *channel);
};

#endif
