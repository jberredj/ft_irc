#include "Command.hpp"
#include "IrcMessages.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include <sstream>

static void _rpl_whoisuser(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(user->getUsername());
	args.push_back(user->getHostname());
	args.push_back(user->getTruename());
	command.replyToInvoker(311, args);
}

static void _rpl_whoishost(Command &command, User *user) {
	if (user->getNickname() != command.getInvoker().getNickname())
		return ;

	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(user->getUsername());
	args.push_back(user->getHostname());
	args.push_back(user->getHostname());
	command.replyToInvoker(378, args);
}

static void _rpl_whoismodes(Command &command, User *user) {
	if (user->getNickname() != command.getInvoker().getNickname())
		return ;

	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(user->getMode());
	command.replyToInvoker(379, args);
}

static void _rpl_whoischannels(Command &command, User *user) {
	std::vector<Channel*> channels = user->getChannels();

	if (channels.empty()) return;

	std::vector<std::string> args;
	typedef std::vector<Channel*>::iterator channel_it;
	args.push_back(user->getNickname());
	for(channel_it channel = channels.begin(); channel != channels.end(); channel++) {
		args.push_back((*channel)->getName()); //TODO: add to arg @ if user is operator
	}

	command.replyToInvoker(319, args);
}

static void _rpl_whoisserver(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(command.getServerName());
	args.push_back("FT_IRC Server"); // TODO: Is that a good server name ? + should not be hardcoded

	command.replyToInvoker(312, args);
}

static void _rpl_whoisidle(Command &command, User *user) {
	std::vector<std::string> args;

	args.push_back(user->getNickname());
	args.push_back(user->getIdle());
	args.push_back(user->getRawSignon());

	command.replyToInvoker(317, args);
}

static void _rpl_endofwhois(Command &command, std::string &nick) {
	std::vector<std::string> args;

	args.push_back(nick);
	command.replyToInvoker(318, args);
}

static void _err_nonicknamegiven(Command &command) {
	std::vector<std::string> args;
	
	command.replyToInvoker(431, args);
}

static void _err_nosuchnick(Command &command, std::string &nick) {
	std::vector<std::string> args;

	args.push_back(nick);
	command.replyToInvoker(401, args);
}

static std::vector<std::string>	_get_target_list(Command &command) {
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
		return _err_nonicknamegiven(command); // 431

	std::vector<std::string> list = _get_target_list(command);
	for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++) {
		User *user = command.getUser(*it);
		
		if (user == NULL) {
			_err_nosuchnick(command, *it); // 401
		} else {
			_rpl_whoisuser(command, user); // 311
			_rpl_whoishost(command, user); // 378
			_rpl_whoischannels(command, user); // 319
			_rpl_whoisserver(command, user); // 312
			_rpl_whoismodes(command, user); // 379
			_rpl_whoisidle(command, user); // 317
		}
		_rpl_endofwhois(command, *it); // 318
	}
}
