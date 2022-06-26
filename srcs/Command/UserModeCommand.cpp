#include "UserModeCommand.hpp"

UserModeCommand::UserModeCommand(Command &command)
: _modeChanges(""), _request(""), _command(command), _invoker(command.getInvoker()), _addSign(true) {
}

void UserModeCommand::updateModes(void) {
	std::vector<std::string> args;
	if (!_command.targetsInvoker())
		return _command.replyToInvoker(502, args);
	_request = _command.getParameters()[1];

	for (size_t i = 0; i < _request.size(); i++)
	{
		_chrMode = _request[i];
		_mode = UserMode::modesMap[_chrMode];
		if (_chrMode == '-')
			_addSign = false;
		else if (_chrMode == '+')
			_addSign = true;
		else if (UserMode::modesMap.count(_chrMode) == 0)
			_command.replyToInvoker(501, args);
		else if (_addSign && _chrMode == 'o')
			continue;
		else if (_addSign && !_invoker.hasMode(_mode))
			_addMode();
		else if (!_addSign && _invoker.hasMode(_mode))
			_removeMode();
	}
	if (!_modeChanges.empty()) {
		args.push_back(_invoker.getNickname());
		args.push_back(_modeChanges);
		_command.invokerSendTo(&_invoker, -5, args);
	}
}

void UserModeCommand::_addMode(void) {
	_invoker.addMode(_mode);
	_modeChanges += "+";
	_modeChanges += _chrMode;
}

void UserModeCommand::_removeMode(void) {
	_invoker.removeMode(_mode);
	_modeChanges += "-";
	_modeChanges += _chrMode;
}