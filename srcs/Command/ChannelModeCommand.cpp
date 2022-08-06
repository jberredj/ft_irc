#include "ChannelModeCommand.hpp"
#include <algorithm>

ChannelModeCommand::ChannelModeCommand(Command &command)
: _command(command), _modeChanges(""), _request(""), _addSign(true), 
_oldSign(_addSign), _firstSign(true), _mode(0), _chrMode('\0'), _currentParamIdx(2) {
}

void ChannelModeCommand::updateModes(void) {
	_channel = _command.getChannel(_command.getParameters()[0]);

	if (!_channel)
		return reply_403(_command);
	if (_command.getParameters().size() == 1)
		return _retrieveChannelModes();

	_request = _command.getParameters()[1];
	for (size_t i = 0; i < _request.size(); i++)
	{
		_chrMode = _request[i];
		if (_chrMode == '-' || _chrMode == '+')
			_updateSign();
		else if (!ChannelMode::modesMap.count(_chrMode))
			_errUnknownMode();
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
	strVec args;

	args.push_back(_channel->getName());
	args.push_back(_channel->getModesList());
	_command.replyToInvoker(324, args);
}

void ChannelModeCommand::_rplCreationTime() {
	strVec args;

	args.push_back(_channel->getName());
	args.push_back(_channel->getRawCreatedAt());
	_command.replyToInvoker(329, args);
}

void ChannelModeCommand::_errCModeMissingParameter(std::string shortMode, std::string longMode, std::string syntax) {
	strVec args;

	args.push_back(_channel->getName());
	args.push_back(shortMode);
	args.push_back(longMode);
	args.push_back(syntax);
	_command.replyToInvoker(696, args); 
}

void ChannelModeCommand::_errChanoPrivsNeeded(std::string lvlop, std::string mode, std::string description) {
	strVec args;

	args.push_back(_channel->getName());
	args.push_back(lvlop);
	args.push_back(mode);
	args.push_back(description);
	_command.replyToInvoker(482, args); 
}

void ChannelModeCommand::_errUnknownMode() {
	strVec args;
	std::string mode;

	mode.push_back(_chrMode);
	args.push_back(mode);
	_command.replyToInvoker(472, args);
}

void ChannelModeCommand::_updateSign(void) {
	if (_chrMode == '-')
		_addSign = false;
	else if (_chrMode == '+')
		_addSign = true;
}

void ChannelModeCommand::_manageMode(void) {
	_mode = ChannelMode::modesMap[_chrMode];
	switch (_mode) {
		case ChannelMode::CMODE_S:
		case ChannelMode::CMODE_I:
		case ChannelMode::CMODE_T:
		case ChannelMode::CMODE_N:
			_manageSimpleFlags();
			break;
		case ChannelMode::CMODE_O:
			_manageChanopFlag();
			break;
		case ChannelMode::CMODE_L:
			_manageLimitFlag();
			break;
	}
}

void ChannelModeCommand::_manageSimpleFlags(void) {
	if (!_channel->isOperator(&_command.getInvoker()))
	{
		if (_mode == ChannelMode::CMODE_S)
			return _errChanoPrivsNeeded("halfop", "s", "secret");
		else if (_mode == ChannelMode::CMODE_I)
			return _errChanoPrivsNeeded("halfop", "i", "inviteonly");
		else if (_mode == ChannelMode::CMODE_T)
			return _errChanoPrivsNeeded("halfop", "t", "topiclock");
		else if (_mode == ChannelMode::CMODE_N)
			return _errChanoPrivsNeeded("halfop", "n", "noextmsg");
	}
	if (_addSign && !_channel->hasMode(_mode))
		_addMode();
	else if (!_addSign && _channel->hasMode(_mode))
		_removeMode();
}

void ChannelModeCommand::_manageLimitFlag(void) {
	if (!_addSign)
		return _removeMode();

	std::string strLimit = _getNextParameter();
	if (strLimit.empty())
		return _errCModeMissingParameter("l", "limit", "limit");

	if (!_channel->isOperator(&_command.getInvoker()))
		return _errChanoPrivsNeeded("halfop", "l", "limit");

	_addMode();
	int limit = std::atoi(strLimit.c_str());
	_channel->setUserLimit(limit);
	_argsToBroadcast.push_back(strLimit);
}

void ChannelModeCommand::_manageChanopFlag(void) {
	std::string target = _getNextParameter();
	if (target.empty())
		return _errCModeMissingParameter("o", "op", "nick");
	
	if (!_channel->isOperator(&_command.getInvoker()))
		return _errChanoPrivsNeeded("op", "o", "op");

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
