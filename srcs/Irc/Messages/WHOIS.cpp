#include "Command.hpp"
#include "IrcMessages.hpp"
#include "Logger.hpp"
#include "User.hpp"

void _rpl_whoisuser(Command &command) {
	std::vector<std::string> args;
	User &user = command.getUser();

	args.push_back(user.getNickname());
	args.push_back(user.getUsername());
	args.push_back(user.getHostname());
	args.push_back(user.getTruename());
	command.replyToInvoker(311, args);
}

void _rpl_whoishost(Command &command) {
	std::vector<std::string> args;
	User &user = command.getUser();

	args.push_back(user.getNickname());
	args.push_back(user.getUsername());
	args.push_back(user.getHostname());
	args.push_back(user.getHostname());
	command.replyToInvoker(378, args);
}

void _rpl_whoismodes(Command &command) {
	std::vector<std::string> args;
	User &user = command.getUser();

	args.push_back(user.getNickname());
	args.push_back(user.getMode());
	command.replyToInvoker(379, args);
}

void _rpl_whoisserver(Command &command) {
	std::vector<std::string> args;
	User &user = command.getUser();

	args.push_back(user.getNickname());
	args.push_back(command.getServerName());
	args.push_back("FT_IRC Server"); // Todo: Is that a good server name ?

	command.replyToInvoker(312, args);
}

void _rpl_whoisidle(Command &command) {
	std::vector<std::string> args;
	User &user = command.getUser();

	args.push_back(user.getNickname());
	args.push_back("12345"); // Todo: replace by idle

	command.replyToInvoker(317, args);
}

void _rpl_endofwhois(Command &command) {
	std::vector<std::string> args;
	User &user = command.getUser();

	args.push_back(user.getNickname());
	command.replyToInvoker(318, args);
}

void WHOIS(Command &command)
{
	_rpl_whoisuser(command);
	_rpl_whoishost(command);
	_rpl_whoisserver(command);
	_rpl_whoismodes(command);
	_rpl_whoisidle(command);
	_rpl_endofwhois(command);
}
