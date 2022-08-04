#ifndef CHANNEL_MODE_COMMAND_HPP
#define CHANNEL_MODE_COMMAND_HPP

#include <string>
#include <stdlib.h> 
#include "User.hpp"
#include "Command.hpp"
#include "helpers.hpp"
#include "ChannelMode.hpp"

class ChannelModeCommand {
public:
	ChannelModeCommand(Command &command);
	void	updateModes(void);

private:
	Command	&_command;
	Channel	*_channel;
	std::string _modeChanges;
	strVec _argsToBroadcast;
	std::string	_request;
	bool	_addSign;
	bool	_oldSign;
	bool	_firstSign;
	uint8_t	_mode;
	char	_chrMode;
	int		_currentParamIdx;

	void	_retrieveChannelModes(void);
	void	_manageMode(void);
	void	_manageChanopFlag(void);
	void	_addMode(void);
	void	_removeMode(void);
	void	_updateSign(void);
	void	_rplChannelmodeis();
	void	_rplCreationTime();
};

#endif
