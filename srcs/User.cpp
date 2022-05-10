/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:16:27 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/10 15:19:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

void WHOIS(Command &command){(void)command;}
void USERS(Command &command){(void)command;}
void USER(Command &command){(void)command;}
void TOPIC(Command &command){(void)command;}
void PRIVMSG(Command &command){(void)command;}
void PONG(Command &command){(void)command;}
void PING(Command &command){(void)command;}
void PASS(Command &command){(void)command;}
void PART(Command &command){(void)command;}
void OPER(Command &command){(void)command;}
void NICK(Command &command){(void)command;}
void NAMES(Command &command){(void)command;}
void MODE(Command &command){(void)command;}
void LIST(Command &command){(void)command;}
void KILL(Command &command){(void)command;}
void KICK(Command &command){(void)command;}
void JOIN(Command &command){(void)command;}
void INVITE(Command &command){(void)command;}
void BAN(Command &command){(void)command;}

std::map<std::string, void (*)(Command &)> User::cmdMap;
void	User::initUserClass(void)
{
	cmdMap["WHOIS"] = WHOIS;
	cmdMap["USERS"] = USERS;
	cmdMap["USER"] = USER;
	cmdMap["TOPIC"] = TOPIC;
	cmdMap["PRIVMSG"] = PRIVMSG;
	cmdMap["PONG"] = PONG;
	cmdMap["PPING"] = PING;
	cmdMap["PASS"] = PASS;
	cmdMap["PART"] = PART;
	cmdMap["OPER"] = OPER;
	cmdMap["NICK"] = NICK;
	cmdMap["NAMES"] = NAMES;
	cmdMap["MODE"] = MODE;
	cmdMap["LIST"] = LIST;
	cmdMap["KILL"] = KILL;
	cmdMap["KICK"] = KICK;
	cmdMap["JOIN"] = JOIN;
	cmdMap["INVITE"] = INVITE;
	cmdMap["BAN"] = BAN;
	Logger::trace("User command map initiated");
}

User::User(void) : commandBuf(""), commandQueue(), responseQueue(), _status(REGISTER),
		_username(""), _nickname(""), _truename(""), _hostname(""), _servaddr(""),  _mode("w"),
		_prevnick(""), _channel("")
{
	Logger::trace("User constructor called");
}

User::User(User const & src)
{
	Logger::trace("User copy contructor called");
	*this = src;
}

User &User::operator=(User const & rhs)
{
	Logger::trace("User assignement operator called");
	if (this != &rhs)
	{
		this->_status = rhs._status;
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
User::~User() {Logger::trace("User destructor called");}

//Getters
UStatus 	User::getUstatus(void) const {return this->_status;}
std::string	User::getUsername(void) const {return this->_username;}
std::string User::getNickname(void) const {return this->_nickname;}
std::string	User::getHostname(void) const {return this->_hostname;}
std::string User::getServaddr(void) const {return this->_servaddr;}
std::string User::getTruename(void) const {return this->_truename;}
std::string User::getMode(void) const {return this->_mode;}
std::string User::getPrevnick(void) const {return this->_prevnick;}
std::string User::getChannel(void) const {return this->_channel;}

//Setters
void		User::setUstatus(UStatus status) {this->_status = status;}
void		User::setUsername(std::string username) {this->_username = username;}
void		User::setNickname(std::string nickname) {this->_nickname = nickname;}
void		User::setHostname(std::string hostname) {this->_hostname = hostname;}
void		User::setServaddr(std::string servaddr) {this->_servaddr = servaddr;}
void		User::setTruename(std::string truename) {this->_truename = truename;}
void		User::setMode(std::string mode) {this->_mode = mode;}
void		User::setPrevnick(std::string prevnick) {this->_prevnick = prevnick;}
void		User::setChannel(std::string channel) {this->_channel = channel;}


void    User::addResponse(std::string response)
{
    responseQueue.push(response);
}

void 	User::addToqueue(Command const & command)
{
	commandQueue.push(command);
}

void    User::apply()
{
	while (!commandQueue.empty())
	{	
		Command &cmd = commandQueue.front();
		commandQueue.pop();
		if (cmdMap.count(cmd.getCommand()) > 0)
			cmdMap[cmd.getCommand()](cmd);
		else
			std::cout << "Uknown command: " << cmd.getCommand() << std::endl;
	}	
}

std::ostream & operator<<(std::ostream & o, User const & rhs)
{
    o << "Username: " << rhs.getUsername() << std::endl;
	o << "Nickname: " << rhs.getNickname() << std::endl;
	o << "Mode: " << rhs.getMode() << std::endl;
    return o;
}