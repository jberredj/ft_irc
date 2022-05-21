/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:16:27 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/21 14:00:27 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <string>
#include <map>
#include "User.hpp"
#include "types/Nullptr_t.hpp"
#include "IrcMessages.hpp"

/* ************************************************************************** */
/*                                  Public                                    */
/* ************************************************************************** */

// Constructors and destructor
User::User(void):
	_commandBuf(""), _commandQueue(), _responseQueue(), _status(PASSWORD),
	_ServerPassword(ft::null_ptr), _username(""), _nickname("-"), _truename(""),
	_hostname(""), _servaddr(""),  _mode("w"), _prevnick(""), _channel("")
{
	_initUserClass();
	Logger(Output::TRACE) << "User constructor called";
}

User::User(const User& src)
{
	Logger(Output::TRACE) << "User copy contructor called";
	*this = src;
}

User::User(std::string* serverPassWd):
	_commandBuf(""), _commandQueue(), _responseQueue(), _status(PASSWORD),
	_ServerPassword(serverPassWd), _username(""), _nickname("-"), _truename(""),
	_hostname("127.0.0.1"), _servaddr(""),  _mode("w"), _prevnick(""), _channel("")
{
	_initUserClass();
	Logger(Output::TRACE) << "User constructor called";
}

User::~User() {Logger(Output::TRACE) << "User destructor called";}

//operators
User &User::operator=(User const & rhs)
{
	Logger(Output::TRACE) << "User assignement operator called";
	if (this != &rhs)
	{
		this->_status = rhs._status;
		this->_ServerPassword = rhs._ServerPassword;
		this->_username = rhs._username;
		this->_nickname = rhs._nickname;
		this->_hostname = rhs._hostname;
		this->_servaddr = rhs._servaddr;
		this->_truename = rhs._truename;
		this->_mode = rhs._mode;
		this->_prevnick = rhs._prevnick;
		this->_channel = rhs._channel;
	}
	return *this;
}

//Getters
User::Status 	User::getStatus(void) const {return this->_status;}
std::string	   	&User::getServerPassword(void) const {return *_ServerPassword;}
std::string	  	User::getPassword(void) const {return _password;}
std::string		User::getUsername(void) const {return this->_username;}
std::string 	User::getNickname(void) const {return this->_nickname;}
std::string		User::getHostname(void) const {return this->_hostname;}
std::string 	User::getServaddr(void) const {return this->_servaddr;}
std::string 	User::getTruename(void) const {return this->_truename;}
std::string 	User::getCommandBuf(void) const {return this->_commandBuf;}
std::string 	User::getMode(void) const {return this->_mode;}
std::string 	User::getPrevnick(void) const {return this->_prevnick;}
std::string 	User::getChannel(void) const {return this->_channel;}
bool			User::repliesAvalaible(void) const 
{
	return !_responseQueue.empty();
}
bool			User::getPassUsed(void) const {return this->_passUsed;}
bool			User::getUserUsed(void) const {return this->_userUsed;}
bool			User::getNickUsed(void) const {return this->_nickUsed;}

void			User::tryAuthentificate(void) const
{
	int response = 0;
	std::vector<std::string> args;
	Command cmd;
	
	if (_passUsed && _userUsed && _nickUsed)
	{
		response = 1;
		args.push_back(getNickname());
		args.push_back(getUsername());
		args.push_back(getHostname());
		return cmd.reply(response, args);
	}	
	else
		std::cout << "Authentification failed" << std::endl;	
}


//Setters
void		User::setStatus(Status status) {this->_status = status;}
void		User::setPassword(std::string password) {this->_password = password;}
void		User::setUsername(std::string username) {this->_username = username;}
void		User::setNickname(std::string nickname) {this->_nickname = nickname;}
void		User::setHostname(std::string hostname) {this->_hostname = hostname;}
void		User::setServaddr(std::string servaddr) {this->_servaddr = servaddr;}
void		User::setTruename(std::string truename) {this->_truename = truename;}

void		User::setCommandBuf(std::string commandBuf)
{
	this->_commandBuf = commandBuf;
}

void		User::appendCommandBuf(std::string commandBuf)
{
	this->_commandBuf += commandBuf;
}

void		User::setMode(std::string mode) {this->_mode = mode;}

void		User::setPrevnick(std::string prevnick)
{
	this->_prevnick = prevnick;
}

void		User::setChannel(std::string channel) {this->_channel = channel;}

bool			User::setPassUsed(void) {return this->_passUsed = false;}
bool			User::setUserUsed(void) {return this->_userUsed = false;}
bool			User::setNickUsed(void) {return this->_nickUsed = false;}



// IO User methods
void 	User::addCommand(Command const & command)
{
	_commandQueue.push(command);
}

void    User::execCommandQueue()
{
	if (!_cmdMap.size())
		throw (std::logic_error("Try to use User Object without initializing it")); 
	while (!_commandQueue.empty())
	{	
		Command &cmd = _commandQueue.front();
		if (_cmdMap.count(cmd.getCommand()) > 0)
		{
			Logger(Output::DEBUG) << cmd;
			_cmdMap[cmd.getCommand()](cmd);
		}
		else
			Logger(Output::INFO) << "Unknown command: " << cmd.getCommand(); 
		_commandQueue.pop();
	}	
}	

void	User::rename(std::string nick)
{
	setPrevnick(getNickname());
	setNickname(nick);
}

void    User::addReply(std::string response)
{
    _responseQueue.push(response);
}

std::string	User::getReplies(void)
{
	std::string	payload("");
	int			payloadSize = 0;

	while (!_responseQueue.empty() && payloadSize + _responseQueue.front().size() + 2 <= IRC_MESSAGE_LEN)
	{
		payloadSize += _responseQueue.front().size() + 2;
		std::string&	reply = _responseQueue.front();
		payload += reply + "\r\n";
		_responseQueue.pop();
	}
	if (payload.empty())
	{
		std::string&	reply = _responseQueue.front();

		payload += reply.substr(0, 509) + "\r\n";
		reply.erase(0, 509);
	}
	return payload;
}

/* ************************************************************************** */
/*                                Non-member                                  */
/* ************************************************************************** */

// Operators
std::ostream & operator<<(std::ostream & o, User const & rhs)
{
    o << "Username: " << rhs.getUsername() << std::endl;
	o << "Nickname: " << rhs.getNickname() << std::endl;
	o << "Mode: " << rhs.getMode() << std::endl;
	o << "User status: " << rhs.getStatus() << std::endl;
    return o;
}