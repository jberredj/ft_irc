/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:38 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/24 17:08:18 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "User.hpp"
#include "Reply.hpp"
#include "typedefs.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "typedefs.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// Constructors and destructor
Command::Command(void) {}

Command::Command(User* invoker, std::string command_line, Server* server):
	_prefix(""), _command(""), _trailer(""), _command_line(command_line),
	_invoker(invoker), _server(server)
{
	std::string delimiter(" ");
	size_t  	position = 0;
	size_t  	i = 0;

	// 1. Look for prefix
	if (command_line[0] == ':')
	{
		position = command_line.find(delimiter);
		_prefix = command_line.substr(0, position);
		i += position + 1;
	}

	// get command line without prefix
	std::string tmp = command_line.substr(i);

	// get command line without trailer & 4. save trailer if any
	if ((position = command_line.substr(i).find(":")) != std::string::npos)
	{
		tmp = tmp.substr(0, position);
		_trailer = command_line.substr(i + position + 1);
	}

	while ((position = tmp.find(delimiter)) != std::string::npos)
	{
		Logger(Output::TRACE) << tmp.substr(0, position);
		_parameters.push_back(tmp.substr(0, position));
		tmp.erase(0, position + delimiter.length());
	}
	_parameters.push_back(tmp);
	// 2. get command word
	_command = *(_parameters.begin());
	// put any command character upper case
	for (size_t j = 0; j < _command.length(); ++j)
		_command[j] = toupper(_command[j]);

	// 3. get parameters if any
	_parameters.erase(_parameters.begin());
	
}

Command::Command(const Command& src): 
	_prefix(src._prefix), _command(src._command), _parameters(src._parameters),
	_trailer(src._trailer), _command_line(src._command_line), _invoker(src._invoker),
	_server(src._server)
{
	Logger(Output::TRACE) << "Command copy constructor called ";
}

Command::~Command(void) {}

// Operators
Command&	Command::operator=(const Command& rhs)
{
	Logger(Output::TRACE) << "Command assignement operator called ";
	_command_line = rhs._command_line;
	_prefix = rhs._prefix;
	_command = rhs._command;
	_parameters = rhs._parameters;
	_invoker = rhs._invoker;
	_trailer = rhs._trailer;
	_server = rhs._server;
	return (*this);
}

// Getters
std::string		Command::getLine(void) const {return _command_line;}
std::string		Command::getPrefix(void) const {return _prefix;}
std::string		Command::getCommand(void) const {return _command;}
const strVec	&Command::getParameters(void) const {return _parameters;}
std::string		Command::getTrailer(void) const {return _trailer;}
User&			Command::getInvoker(void) const {return *_invoker;}
User*			Command::getUser(std::string nickname) const {
	return _server->getUser(nickname);
}

std::vector<User *>*	Command::getUsers(void) {return _server->getUsers();}

// Server*	Command::getServer(void) const {
// 	return _server;
// }

std::string	Command::getServerPassword(void) const {
	return _server->getPassword();
}

User*	Command::getOldUser(std::string nickname)
{
	return _server->getOldUser(nickname);
}

std::vector<User *>*	Command::getOldUsers(void) {return _server->getOldUsers();}

std::string	Command::getServerName(void) const
{
	return _server->getServerName();
}

// Channel*	Command::getChannel(std::string name, bool errorOut) {
// 	Channel *channel = _server->getChannel(name);
// 	if (!channel && errorOut)
// 	{
// 		strVec	args;
// 		args.push_back(name);
// 		replyToInvoker(403, args);
// 	}
// 	return channel;
// }

Channel*	Command::getChannel(std::string name) {
	return _server->getChannel(name);
}

std::map<std::string, Channel*>*	Command::getChannels(void) {return _server->getChannels();}
void	Command::addChannel(Channel *channel) {_server->addChannel(channel);}

bool	Command::targetsInvoker(void) const {
	return (getParameters().front() == getInvoker().getNickname());
}

bool	Command::existingTarget(void) const {
	return (getUser(_parameters.front()));
}

// Replies functions

void	Command::replyAllReachable(std::string message)
{
	std::vector<Channel*> channels(_invoker->getChannels());
	userVec	uniqueUser;

	for (channelIterator it = channels.begin(); it != channels.end(); it++)
	{
		userVec channelUser = (*it)->getMembers();
		userVec merged;
		std::sort(channelUser.begin(), channelUser.end());
		std::merge(uniqueUser.begin(), uniqueUser.end(), 
			channelUser.begin(), channelUser.end(), std::back_inserter(merged));
		userVec::iterator dupesIt = std::unique(merged.begin(), merged.end());
		merged.erase(dupesIt, merged.end());
		uniqueUser = merged;
	}
	for (userVec::iterator it = uniqueUser.begin(); it != uniqueUser.end(); it++)
		if (*it != _invoker)
			(*it)->addReply(message);
}

void	Command::replyAllReachable(int code, strVec args)
{
	replyAllReachable(_reply(_invoker, ft::null_ptr, code, args));
}

void	Command::replyToInvoker(int code, strVec args)
{
	_invoker->addReply(_reply(ft::null_ptr, _invoker, code, args));
}

void	Command::invokerSendTo(User* receiver, int code, strVec args)
{
	receiver->addReply(_reply(_invoker, receiver, code, args));
}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

// Replies functions
std::string	Command::_reply(User* sender, User* receiver, int code, strVec args)
{
	std::string	reply;
	std::stringstream	codeString;

	reply = ":";
	if (!sender)
		reply += _server->getServerName() + " ";
	else
		reply += sender->getPrefix() + " ";
	if (code > 0)
	{
		codeString << std::setw(3) << std::setfill('0') << code;
		reply += codeString.str() + " ";
		reply += receiver->getNickname() + " ";
	}
	reply += Reply().getReply(code, args);
	return reply;
}

/* ************************************************************************** */
/*                                Non-member                                  */
/* ************************************************************************** */

// Operators
std::ostream&	operator<<(std::ostream& o, const Command& rhs)
{
	o << "Line: " << rhs.getLine() << std::endl;
	o << "Prefix : "  << rhs.getPrefix() << std::endl;
	o << "Command : " << rhs.getCommand() << std::endl;
	o << "Parameters : " << std::endl;
	strVec	tmp = rhs.getParameters();
	for (strVec::iterator it = tmp.begin(); 
		it != tmp.end(); ++it)
		o << "\t" << *it << std::endl;
	o << "Trailer : " << rhs.getTrailer() << std::endl;
	return o;
}
