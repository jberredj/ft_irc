/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:16:27 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/13 19:54:59 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <string>
#include <map>
#include <sstream>
#include "User.hpp"
#include "types/Nullptr_t.hpp"
#include "IrcMessages.hpp"

/* ************************************************************************** */
/*                                  Public                                    */
/* ************************************************************************** */

// Constructors and destructor

User::User(const User& src)
{
	Logger(Output::TRACE) << "User copy contructor called";
	*this = src;
}

User::User(void):
	_commandBuf(""), _commandQueue(), _responseQueue(), _status(PASSWORD),
	_password(""), _username(""), _nickname("*"), _truename(""),
	_hostname("127.0.0.1"), _mode(""), _signon(std::time(ft::null_ptr))
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
		// this->_ServerPassword = rhs._ServerPassword;
		this->_username = rhs._username;
		this->_nickname = rhs._nickname;
		this->_hostname = rhs._hostname;
		this->_truename = rhs._truename;
		this->_mode = rhs._mode;
		this->_signon = rhs._signon;
	}
	return *this;
}

//Getters
User::Status 	User::getStatus(void) const {return this->_status;}
std::string		User::getUsername(void) const {return this->_username;}
std::string 	User::getNickname(void) const {return this->_nickname;}
std::string		User::getHostname(void) const {return this->_hostname;}
std::string 	User::getTruename(void) const {return this->_truename;}
std::string 	User::getCommandBuf(void) const {return this->_commandBuf;}
std::string 	User::getMode(void) const {return this->_mode;}
bool			User::repliesAvalaible(void) const {return !_responseQueue.empty();}

std::string	 	User::getRawSignon(void) const {
	std::stringstream ss;
	ss << static_cast<long>(_signon);
	return ss.str();
}

std::string		User::getSignon(void) const {
	struct tm *timeinfo = localtime(&_signon);
	char buffer[512];
	if (!strftime(buffer, sizeof(buffer), "%a %b %d %Y %H:%M:%S", timeinfo))
		buffer[0] = '\0';
	return std::string(buffer);
}

std::string		User::getIdle(void) const {
	time_t rawIdle = std::time(ft::null_ptr) - this->_signon;
	std::stringstream ss;
	ss << static_cast<long>(rawIdle);
	return ss.str();
}

std::string		User::getPrefix(void) const
{
	if (_status == PASSWORD || _status == REGISTER)
		return "";
	std::string	prefix(_nickname);
	if (_hostname.length())
	{
		if (_username.length())
			prefix += "!" + _username;
		prefix += "@" + _hostname;
	}
	return prefix;
}

void			User::tryAuthentificate(Command &cmd)
{
	int response = 0;
	std::vector<std::string> args;
	
	if (!_password.length()) return;
	if (!_username.length()) return;
	if (_nickname == "*") return;

	if (_password == cmd.getServerPassword())
	{
		response = 1;
		args.push_back(_nickname);
		args.push_back(_username);
		args.push_back(_hostname);
		setStatus(ONLINE);
		return cmd.replyToInvoker(response, args);
	}	
	else
	{
		Logger(Output::INFO) << "Authentification failed";
		setStatus(OFFLINE);
	}
}


//Setters
void		User::setStatus(Status status) {this->_status = status;}
void		User::setPassword(std::string password) {this->_password = password;}
void		User::setUsername(std::string username) {this->_username = username;}
void		User::setNickname(std::string nickname) {this->_nickname = nickname;}
void		User::setHostname(std::string hostname) {this->_hostname = hostname;}
void		User::setTruename(std::string truename) {this->_truename = truename;}

void		User::setCommandBuf(std::string commandBuf)
{
	this->_commandBuf = commandBuf;
}
void		User::clearCommandBuff(void) {this->_commandBuf.clear();}
void		User::appendCommandBuf(std::string commandBuf)
{
	this->_commandBuf += commandBuf;
}

void		User::setMode(std::string mode) {this->_mode = mode;}

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
			Logger(Output::TRACE) << cmd;
			_cmdMap[cmd.getCommand()](cmd);
		}
		else
			Logger(Output::INFO) << "Unknown command: " << cmd.getCommand(); 
		_commandQueue.pop();
	}	
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
	o << "Connected since: " << rhs.getSignon() << std::endl;
    return o;
}