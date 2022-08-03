#include "ChannelModeCommand.hpp"

ChannelModeCommand::ChannelModeCommand(Command &command)
: _command(command), _invoker(command.getInvoker()) {
}

void ChannelModeCommand::updateModes(void) {
	if (_command.getParameters().size() == 1)
		return _retrieveChannelModes();

	// Mode changes are broadcast to all members
		// :foo!tokino@172.17.0.1 MODE #tardis :+p
		// Rename RPL_SETUSERMODE and use it !
}

void ChannelModeCommand::_retrieveChannelModes(void) {
	// channel = GetChannel
    // If channel does not exist
        // :cdc7a5be35e6.example.com 403 foo #tardis :No such channel
    // Else If invoker is not in channel, channel exist but is private (mode p) or secret (mode s)
        // :cdc7a5be35e6.example.com 403 bar #tardis :No such channel
    // Else If invoker is not in channel (but channel exist)
        // :cdc7a5be35e6.example.com 324 bar #tardis :+nt
        // :cdc7a5be35e6.example.com 329 bar #tardis :1656401335
    // Else If Invoker is in channel (no matter he's chanop or not) // Note: Useless condition
		// :f10c4f1ecd09.example.com 324 foo #tardis :+inpt
		// :f10c4f1ecd09.example.com 329 foo #tardis :1656335996

	Channel*	channel = _command.getChannel(_command.getParameters()[0]);
	if (!channel)
		return reply_403(_command);
    if (!channel->isMember(&_invoker) && (channel->hasMode(ChannelMode::CMODE_S)))
		return reply_403(_command);

	_rplChannelmodeis();
	_rplCreationTime(channel);
}

void ChannelModeCommand::_rplChannelmodeis() {
	std::vector<std::string> args;

	args.push_back(_invoker.getModesList());
	_command.replyToInvoker(324, args);
}

void ChannelModeCommand::_rplCreationTime(Channel *channel) {
	std::vector<std::string> args;

	args.push_back(channel->getRawCreatedAt());
	_command.replyToInvoker(329, args);
}