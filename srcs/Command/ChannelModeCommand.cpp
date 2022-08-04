#include "ChannelModeCommand.hpp"
#include <algorithm>

ChannelModeCommand::ChannelModeCommand(Command &command)
: _command(command), _currentParamIdx(2) {
}

void ChannelModeCommand::updateModes(void) {
	_channel = _command.getChannel(_command.getParameters()[0]);

	if (!_channel)
		return reply_403(_command);
	if (_command.getParameters().size() == 1)
		return _retrieveChannelModes();
	
	// TODO - Is there some cases the user cant change channel modes ?

	_request = _command.getParameters()[1];

	for (size_t i = 0; i < _request.size(); i++)
	{
		_chrMode = _request[i];
		_mode = ChannelMode::modesMap[_chrMode];
		if (_chrMode == '-' || _chrMode == '+')
			_updateSign();
		else if (ChannelMode::modesMap.count(_chrMode) == 0) // mode not found
			; // TODO - 472
		else
			_manageMode();
	}

	// Mode changes are broadcast to all members
	if (!_modeChanges.empty()) {
		std::string	message = ":" + _command.getInvoker().getPrefix() + " MODE " + _channel->getName() + " :" + _modeChanges;
		for (strVecIterator it = _argsToBroadcast.begin(); it != _argsToBroadcast.end(); it++)
			message += " " + *it;
		_channel->broadcastMessage(message);
	}
}

void ChannelModeCommand::_retrieveChannelModes(void) {
    if (!_channel->isMember(&_command.getInvoker()) && (_channel->hasMode(ChannelMode::CMODE_S)))
		return reply_403(_command);

	_rplChannelmodeis();
	_rplCreationTime();
}

void ChannelModeCommand::_rplChannelmodeis() {
	std::vector<std::string> args;

	args.push_back(_channel->getName());
	args.push_back(_channel->getModesList());
	_command.replyToInvoker(324, args);
}

void ChannelModeCommand::_rplCreationTime() {
	std::vector<std::string> args;

	args.push_back(_channel->getName());
	args.push_back(_channel->getRawCreatedAt());
	_command.replyToInvoker(329, args);
}

void ChannelModeCommand::_updateSign(void) {
	if (_chrMode == '-')
		_addSign = false;
	else if (_chrMode == '+')
		_addSign = true;
}

void ChannelModeCommand::_manageMode(void) {
	switch (_mode) {
		case ChannelMode::CMODE_S:
		case ChannelMode::CMODE_I:
		case ChannelMode::CMODE_T:
		case ChannelMode::CMODE_N:
			_addSign ? _addMode() : _removeMode();
			break;
		case ChannelMode::CMODE_O:
			_manageChanopFlag();
			break;
		case ChannelMode::CMODE_B:
			; // TODO - Add ban mask (simpler, add arg to ban list users)
			break;
		case ChannelMode::CMODE_L:
			if (_addSign) {
				std::string strLimit = _getNextParameter();
				if (strLimit.empty()) {
					return ; // TODO - :30dcca498ab0.example.com 696 foo #tardis l * :You must specify a parameter for the limit mode. Syntax: <limit>.
				}
				_addMode();
				int limit = std::atoi(strLimit.c_str());
				_channel->setUserLimit(limit);
				_argsToBroadcast.push_back(strLimit);
			} else {
				_removeMode();
			}
			break;
	}
}

void ChannelModeCommand::_manageChanopFlag(void) {
	std::string target = _getNextParameter(); // Seems we do not have to split on comma ?!
	if (target.empty()) {
		return ; // TODO - :30dcca498ab0.example.com 696 foo #tardis o * :You must specify a parameter for the op mode. Syntax: <nick>.
	}

	User * user = _command.getUser(target);
	if (!user) {
		strVec args;
		args.push_back(target);
		return _command.replyToInvoker(401, args);
	}
	else if (!_channel->isMember(user)) // if target is not member of channel (no matter -o or +o)
		; // do nothing
	else if (_addSign && !isUserChanop(_channel, user)) {
		_addMode();
		std::string curModes = _channel->getUserMode(user);
		_channel->setUserMode(curModes.append("o"), user);
		_argsToBroadcast.push_back(user->getNickname());
	}
	else if (!_addSign && isUserChanop(_channel, user)) {
		_removeMode();
		std::string curModes = _channel->getUserMode(user);
		curModes.erase(std::remove(curModes.begin(), curModes.end(), 'o'), curModes.end());
		_channel->setUserMode(curModes, user);
		_argsToBroadcast.push_back(user->getNickname());
	}
	// else target is not chanop and flag is -o  OR  if target is already chanop, and flag is +o
		// do nothing
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

std::string ChannelModeCommand::_getNextParameter(void) {
	std::string param;
	if (_currentParamIdx < static_cast<int>(_command.getParameters().size())) {
		param = _command.getParameters()[_currentParamIdx];
		_currentParamIdx++;
	} else {
		param = "";
	}
	return param;

}
