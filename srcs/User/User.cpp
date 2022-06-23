/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:16:27 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/23 16:14:59 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include "User.hpp"
#include "typedefs.hpp"
#include "IrcMessages.hpp"

/* ************************************************************************** */
/*                                  Public                                    */
/* ************************************************************************** */

// Constructors and destructor

User::User(void):
	_commandBuf(""), _commandQueue(), _responseQueue(), _status(PASSWORD),
	_password(""), _username(""), _nickname("*"), _truename(""),
	_hostname("127.0.0.1"), _modes(), _awayMsg(""), _signon(std::time(ft::null_ptr)), _channels()
{
	_initUserClass();
	Logger(Output::TRACE) << "User constructor called";
}

User::User(const User& src)
{
	Logger(Output::TRACE) << "User copy contructor called";
	*this = src;
}

User::~User() {
	Logger(Output::TRACE) << "User destructor called";
	channelIterator it = _channels.begin(); 
	while (it != _channels.end())
	{
		(*it)->removeUser(this);
		channelIterator it = _channels.begin();
		(void)it; // TODO: Find a way to remove the need of this
	}
	_channels.clear();
}

//operators
User &User::operator=(User const & rhs)
{
	Logger(Output::TRACE) << "User assignement operator called";
	if (this != &rhs)
	{
		this->_status = rhs._status;
		this->_username = rhs._username;
		this->_nickname = rhs._nickname;
		this->_hostname = rhs._hostname;
		this->_truename = rhs._truename;
		this->_modes = rhs._modes;
		this->_awayMsg = rhs._awayMsg;
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
std::string		User::getModesList(void) const {return _modes.getStrModes();}
std::string		User::getAwaymsg(void) const {return this->_awayMsg;}
bool			User::repliesAvalaible(void) const {return !_responseQueue.empty();}
std::vector<Channel*>	User::getChannels(void) {return _channels;}

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
		args.push_back(getPrefix());
		setStatus(ONLINE);
		return cmd.replyToInvoker(response, args);
	}	
	else
	{
		Logger(Output::INFO) << "Authentification failed";
		setStatus(OFFLINE);
	}
}

bool			User::isAway(void)
{
	return !_awayMsg.empty();
}

bool	User::isOperator(void) const {
	return (_modes.hasMode(UserMode::UMODE_O));
}

//Setters
void	User::setStatus(Status status) {this->_status = status;}
void	User::setPassword(std::string password) {this->_password = password;}
void	User::setUsername(std::string username) {this->_username = username;}
void	User::setNickname(std::string nickname) {this->_nickname = nickname;}
void	User::setHostname(std::string hostname) {this->_hostname = hostname;}
void	User::setTruename(std::string truename) {this->_truename = truename;}
void	User::addMode(uint8_t mode) {_modes.addMode(mode);}
void	User::removeMode(uint8_t mode) {_modes.removeMode(mode);}
bool	User::hasMode(uint8_t mode) {return _modes.hasMode(mode);}
void	User::setAwayMsg(std::string msg) {this->_awayMsg = msg;}

void	User::setCommandBuf(std::string commandBuf) {
	this->_commandBuf = commandBuf;
}
void	User::clearCommandBuff(void) {
	this->_commandBuf.clear();
}
void	User::appendCommandBuf(std::string commandBuf) {
	this->_commandBuf += commandBuf;
}

void	User::addChannelToUser(Channel *channel) {
	_channels.push_back(channel);
}

void	User::removeChannelFromUser(Channel *channel) {

	channelIterator it = std::find(_channels.begin(), _channels.end(), channel);
	_channels.erase(it);
}

void	User::clearChannels(void) {_channels.clear();}

// IO User methods
void 	User::addCommand(Command const & command) {
	_commandQueue.push(command);
}

void	User::clearCommandQueue(void)
{
	while(!_commandQueue.empty())
		_commandQueue.pop();
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

void	User::clearReplies(void) 
{
	while (!_responseQueue.empty())
	{
		_responseQueue.pop();
	}
}

/* ************************************************************************** */
/*                                Non-member                                  */
/* ************************************************************************** */

// Operators
std::ostream & operator<<(std::ostream & o, User const & rhs)
{
    o << "Username: " << rhs.getUsername() << std::endl;
	o << "Nickname: " << rhs.getNickname() << std::endl;
	o << "Mode: " << rhs.getModesList() << std::endl;
	o << "User status: " << rhs.getStatus() << std::endl;
	o << "Connected since: " << rhs.getSignon() << std::endl;
    return o;
}