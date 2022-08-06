#include "UserModeCommand.hpp"

UserModeCommand::UserModeCommand(Command &command)
: _command(command), _invoker(command.getInvoker()), _modeChanges(""),
_request(""), _addSign(true), _oldSign(_addSign), _firstSign(true),
_mode(0), _chrMode('\0') {
}

void UserModeCommand::updateModes(void) {
	std::vector<std::string> args;

	if (_command.getParameters().size() == 1)
		return _retrieveTargetModes();
	if (!_command.targetsInvoker()) {
		args.push_back("Can't change mode");
		return _command.replyToInvoker(502, args);
	}

	_request = _command.getParameters()[1];

	for (size_t i = 0; i < _request.size(); i++)
	{
		_chrMode = _request[i];
		if (UserMode::modesMap.count(_chrMode))
			_mode = UserMode::modesMap[_chrMode];

		if (_chrMode == '-' || _chrMode == '+')
			_updateSign();
		else if (!UserMode::modesMap.count(_chrMode))
			_command.replyToInvoker(501, args);
		else if (_addSign && _chrMode == 'o')
			continue;
		else if (_addSign && !_invoker.hasMode(_mode))
			_addMode();
		else if (!_addSign && _invoker.hasMode(_mode))
			_removeMode();
	}
	_sendReply();
}

void UserModeCommand::_retrieveTargetModes(void) {
	std::vector<std::string> args;
	if (_command.targetsInvoker()) {
		args.push_back(_invoker.getModesList());
		return _command.replyToInvoker(221, args);
	}
	
	if (_command.existingTarget()) {
		args.push_back("Can't view modes");
		return _command.replyToInvoker(502, args);
	}

	args.push_back(_command.getParameters()[0]);
	_command.replyToInvoker(401, args);
}

void UserModeCommand::_addMode(void) {
	_invoker.addMode(_mode);
	if (_oldSign != _addSign || _firstSign) {
		_modeChanges += "+";
		_firstSign = false;
	}
	_modeChanges += _chrMode;
	_oldSign = _addSign;
}

void UserModeCommand::_removeMode(void) {
	_invoker.removeMode(_mode);
	if (_oldSign != _addSign || _firstSign) {
		_modeChanges += "-";
		_firstSign = false;
	}
	_modeChanges += _chrMode;
	_oldSign = _addSign;
}

void UserModeCommand::_updateSign(void) {
	if (_chrMode == '-')
		_addSign = false;
	else if (_chrMode == '+')
		_addSign = true;
}

void UserModeCommand::_sendReply(void) {
	std::vector<std::string> args;
	if (!_modeChanges.empty()) {
		args.push_back(_invoker.getNickname());
		args.push_back(_modeChanges);
		_command.invokerSendTo(&_invoker, -5, args);
	}
}
