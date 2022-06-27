#include "ChannelModeCommand.hpp"

ChannelModeCommand::ChannelModeCommand(Command &command)
: _command(command), _invoker(command.getInvoker()) {
}

void ChannelModeCommand::updateModes(void) {
    if (_command.getParameters().size() == 1)
		return _retrieveChannelModes();
}

void ChannelModeCommand::_retrieveChannelModes(void) {
    // If invoker is not in channel (but channel exist)cdgfhjel
    // If Invoker is in channel (no matter he's chanop or not)
        // :f10c4f1ecd09.example.com 324 foo #tardis :+inpt
        // :f10c4f1ecd09.example.com 329 foo #tardis :1656335996

    if ()
}