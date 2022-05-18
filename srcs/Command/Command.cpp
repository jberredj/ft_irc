/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:38 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/18 19:23:38 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "User.hpp"
#include "Reply.hpp"
#include "typedefs.hpp"
#include <algorithm>

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// Constructors and destructor
Command::Command(void) {}

Command::Command(User* user, std::string command_line, std::vector<User *>* users):
	_prefix(""), _command(""), _trailer(""), _command_line(command_line),
	_user(user), _allUsers(users)
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
	_trailer(src._trailer), _command_line(src._command_line), _user(src._user),
	_allUsers(src._allUsers)
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
	_user = rhs._user;
	_trailer = rhs._trailer;
	_allUsers = rhs._allUsers;
	return (*this);
}

// Getters
std::string	Command::getLine(void) const {return _command_line;}
std::string	Command::getPrefix(void) const {return _prefix;}
std::string	Command::getCommand(void) const {return _command;}

std::vector<std::string>	Command::getParameters(void) const 
{
	return _parameters;
}

std::string	Command::getTrailer(void) const {return _trailer;}
User&	Command::getUser(void) const {return *_user;}

User*	Command::getUser(std::string nickname)
{
	_nickToFind = nickname;
	std::vector<User *>::iterator find;

	find = std::find_if(_allUsers->begin(), _allUsers->end(), _nickFinder);
	_nickToFind.clear();
	if (find == _allUsers->end())
		return ft::null_ptr;
	return (*find);	
}

std::vector<User *>*	Command::getUsers(void) {return _allUsers;}

// Replies functions
void	Command::replyTo(User *user, int code, std::vector<std::string> args)
{
	std::string	reply;
	Logger(Output::WARN) << "Incomplete Replies";
	reply = Reply().getReply(code, args);
	user->addReply(reply);
}

void	Command::replyAll(int code, std::vector<std::string> args)
{
	(void)code;
	(void)args;
	Logger(Output::WARN) << "replyAll() not implemented yet";
}

void	Command::reply(int code, std::vector<std::string> args)
{
	replyTo(_user, code, args);
}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

std::string	Command::_nickToFind;

bool	Command::_nickFinder(User *user)
{
	if (user)
	{
		if (user->getNickname() == _nickToFind)
			return true;
	}
	return false;
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
	std::vector<std::string>	tmp = rhs.getParameters();
	for (std::vector<std::string>::iterator it = tmp.begin(); 
		it != tmp.end(); ++it)
		o << "\t" << *it << std::endl;
	o << "Trailer : " << rhs.getTrailer() << std::endl;
	return o;
}
