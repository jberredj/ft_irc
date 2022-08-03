#include <cstdlib>
#include <climits>
#include "Command.hpp"
#include "IrcMessages.hpp"
#include "Logger.hpp"
#include "User.hpp"

static void _err_nonicknamegiven(Command &command) {
	std::vector<std::string> args;
	
	command.replyToInvoker(431, args);
}

static void _err_wasnosuchnick(Command &command, std::string &nick) {
	std::vector<std::string> args;

	args.push_back(nick);
	command.replyToInvoker(406, args);
}

static void _rpl_whowasuser(Command &command, User &user) {
	std::vector<std::string> args;

	args.push_back(user.getNickname());
	args.push_back(user.getUsername());
	args.push_back(user.getHostname());
	args.push_back(user.getTruename());
	command.replyToInvoker(314, args);
}

static void _rpl_endofwhowas(Command &command, std::string &nick) {
	std::vector<std::string> args;

	args.push_back(nick);
	command.replyToInvoker(369, args);
}

static void _rpl_whoisserver(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(command.getServerName());
	args.push_back(user->getSignon());

	command.replyToInvoker(312, args);
}

void WHOWAS(Command &command)
{
	if (command.getParameters().size() == 0)
		return _err_nonicknamegiven(command); // 431

	std::vector<User*>* users = command.getOldUsers();
	std::string searchedNick = command.getParameters()[0];

	long maxDisplay = 0;
	if (command.getParameters().size() >= 2)
		maxDisplay = std::strtol(command.getParameters()[1].c_str(), NULL, 10);
	if (maxDisplay == 0)
		maxDisplay = INT_MAX;

	std::vector<User*>::iterator it = users->begin();
	long count = 0;
	while(count < maxDisplay && it != users->end()) {
		if ((*it)->getNickname() == searchedNick) {
			User *user = command.getOldUser(searchedNick);
			_rpl_whowasuser(command, *user); // 314
			_rpl_whoisserver(command, *it); // 312
			count++;
		}
		it++;
	}
	if (count == 0)
		_err_wasnosuchnick(command, searchedNick); // 406
	_rpl_endofwhowas(command, searchedNick); // 369
}
