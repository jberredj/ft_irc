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
	User	&_invoker;

	void _retrieveChannelModes(void);

};

#endif
