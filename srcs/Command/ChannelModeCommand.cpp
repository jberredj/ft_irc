#include "ChannelModeCommand.hpp"

ChannelModeCommand::ChannelModeCommand(Command &command)
: _command(command), _currentParamIdx(2) {
}

void ChannelModeCommand::updateModes(void) {
	_channel = _command.getChannel(_command.getParameters()[0]);

	if (!_channel)
		return reply_403(_command);
	if (_command.getParameters().size() == 1)
		return _retrieveChannelModes();
	
	// Is there some cases the user cant change channel modes ?

	_request = _command.getParameters()[1];
	// _currentParam = _command.getParameters()[_currentParamIdx];

	for (size_t i = 0; i < _request.size(); i++)
	{
		_chrMode = _request[i];
		_mode = ChannelMode::modesMap[_chrMode];
		if (_chrMode == '-' || _chrMode == '+')
			_updateSign();
		else if (ChannelMode::modesMap.count(_chrMode) == 0)
			; // TODO - 472
		else if (_addSign && !_channel->hasMode(_mode)) // TODO -  Adapt condition to channel
			_addMode();
		else if (!_addSign && _channel->hasMode(_mode)) // TODO -  Adapt condition to channel
			_removeMode();
	}

	// Mode changes are broadcast to all members
		// :foo!tokino@172.17.0.1 MODE #tardis :+p
		// Rename RPL_SETUSERMODE and use it !
}

void ChannelModeCommand::_retrieveChannelModes(void) {
    if (!_channel->isMember(&_command.getInvoker()) && (_channel->hasMode(ChannelMode::CMODE_S)))
		return reply_403(_command);

	_rplChannelmodeis();
	_rplCreationTime(_channel);
}

void ChannelModeCommand::_rplChannelmodeis() {
	std::vector<std::string> args;

	args.push_back(_channel->getModesList());
	_command.replyToInvoker(324, args);
}

void ChannelModeCommand::_rplCreationTime(Channel *channel) {
	std::vector<std::string> args;

	args.push_back(channel->getRawCreatedAt());
	_command.replyToInvoker(329, args);
}

void ChannelModeCommand::_updateSign(void) {
	if (_chrMode == '-')
		_addSign = false;
	else if (_chrMode == '+')
		_addSign = true;
}

void ChannelModeCommand::_addMode(void) {
	_channel->addMode(_mode);
	if (_oldSign != _addSign || _firstSign) {
		_modeChanges += "+";
		_firstSign = false;
	}
	_modeChanges += _chrMode;
	_oldSign = _addSign;
}

void ChannelModeCommand::_removeMode(void) {
	_channel->removeMode(_mode);
	if (_oldSign != _addSign || _firstSign) {
		_modeChanges += "-";
		_firstSign = false;
	}
	_modeChanges += _chrMode;
	_oldSign = _addSign;
}