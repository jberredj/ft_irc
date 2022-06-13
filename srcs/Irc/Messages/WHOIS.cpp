#include "Command.hpp"
#include "IrcMessages.hpp"
#include "Logger.hpp"
#include "User.hpp"

void _rpl_whoisuser(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(user->getUsername());
	args.push_back(user->getHostname());
	args.push_back(user->getTruename());
	command.replyToInvoker(311, args);
}

void _rpl_whoishost(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(user->getUsername());
	args.push_back(user->getHostname());
	args.push_back(user->getHostname());
	command.replyToInvoker(378, args);
}

void _rpl_whoismodes(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(user->getMode());
	command.replyToInvoker(379, args);
}

void _rpl_whoisserver(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(command.getServerName());
	args.push_back("FT_IRC Server"); // TODO: Is that a good server name ? + should not be hardcoded

	command.replyToInvoker(312, args);
}

void _rpl_whoisidle(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back("12345"); // TODO: replace by idle

	command.replyToInvoker(317, args);
}

void _rpl_endofwhois(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	command.replyToInvoker(318, args);
}

void _err_nonicknamegiven(Command &command) {
	std::vector<std::string> args;
	
	command.replyToInvoker(431, args);
}

void WHOIS(Command &command) // TODO : Add 319 WHOISCHANNELS and 313 RPL_WHOISOPERATOR
{
	std::vector<User *> *users = command.getUsers();

	if (command.getParameters().size() == 0)
		_err_nonicknamegiven(command);

	for(std::vector<User *>::iterator user = users->begin(); user != users->end(); user++) {
		_rpl_whoisuser(command, *user);
		if ((*user)->getNickname() == command.getUser().getNickname())
			_rpl_whoishost(command, *user);

		_rpl_whoisserver(command, *user);
		if ((*user)->getNickname() == command.getUser().getNickname())
			_rpl_whoismodes(command, *user);
		
		_rpl_whoisidle(command, *user);
		_rpl_endofwhois(command, *user);
	}
}
