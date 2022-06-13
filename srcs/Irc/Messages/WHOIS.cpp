#include "Command.hpp"
#include "IrcMessages.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include <sstream>

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

void _rpl_endofwhois(Command &command, std::string &nick) {
	std::vector<std::string> args;

	args.push_back(nick);
	command.replyToInvoker(318, args);
}

void _err_nonicknamegiven(Command &command) {
	std::vector<std::string> args;
	
	command.replyToInvoker(431, args);
}

void _err_nosuchnick(Command &command, std::string &nick) {
	std::vector<std::string> args;

	args.push_back(nick);
	command.replyToInvoker(401, args);
}

std::vector<std::string>	_get_target_list(Command &command) {
	std::string param = command.getParameters()[0];
	std::istringstream iss(param);
	std::vector<std::string> target_list;

	std::string target_name;
	while (std::getline(iss, target_name, ','))
		target_list.push_back(target_name);
	return target_list;
}

void WHOIS(Command &command) // TODO : Channel update, add 319 WHOISCHANNELS and 313 RPL_WHOISOPERATOR
{
	if (command.getParameters().size() == 0)
		_err_nonicknamegiven(command);

	std::vector<std::string> list = _get_target_list(command);
	for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++) {
		User *user = command.getUser(*it);
		
		if (user == NULL) {
			_err_nosuchnick(command, *it);
		} else {
			_rpl_whoisuser(command, user);
			if (user->getNickname() == command.getUser().getNickname())
				_rpl_whoishost(command, user);

			_rpl_whoisserver(command, user);
			if (user->getNickname() == command.getUser().getNickname())
				_rpl_whoismodes(command, user);
			
			_rpl_whoisidle(command, user);
		}
		_rpl_endofwhois(command, *it);
	}
}
