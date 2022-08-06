/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:28:19 by jberredj          #+#    #+#             */
/*   Updated: 2022/08/06 16:09:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <sstream>
#include "typedefs.hpp"
#include "Logger.hpp"
#include <poll.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// Constructors and destructor
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

Server::Server(int ac, char** av):
	_exitCode(0), _serverName("irc.CTPT.fr")
{
	if (ac != 3)
	{
		throw(std::runtime_error("usage: " + std::string(av[0]) +
			" <port> <password>"));
	}
	if  (!is_number((char*)av[1]))
		throw(std::runtime_error("Port must be a number."));
	Logger(Output::INFO) << "Requested port: " << av[1];
	signal(SIGINT, Server::_SigIntHandler);
	_preparePollfds();
	_serverSocket = _createServerSocket((char*)av[1]);
	_pollfds[0].fd = _serverSocket;
	_password = av[2];
	_running = true;
}

Server::~Server(void)
{
	for(std::vector<User *>::iterator it = _users.begin(); it < _users.end(); it++)
		delete (*it);
	for(std::vector<User *>::iterator it = _oldUsers.begin(); it < _oldUsers.end(); it++)
		delete (*it);
	for(std::vector<struct pollfd>::iterator it = _pollfds.begin();
		it != _pollfds.end(); it++)
			close((*it).fd);
	for(std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
		if ((*it).second)
			delete (*it).second;
	close(_serverSocket);
}

// Getters
std::string	Server::getServerName(void) const {return this->_serverName;}

short	Server::getExitCode(void) const {return _exitCode;}

// Setters
void	Server::setServerName(std::string serverName)
{
	this->_serverName = serverName;
}

std::string	Server::getPassword(void) const {return _password;}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

// Static variable initialisation
bool Server::_sigInt = false;

// Constructors
Server::Server(void):
	_exitCode(0), _serverName("irc.CTPT.fr")
{
	_preparePollfds();
}

// General methods and functions
void	Server::_SigIntHandler(int signum)
{
	(void)signum;
	Server::_sigInt = true;
}

void	Server::_logRawMessage(char *buf, User &user, std::string prefix)
{
	std::string				rawMessage(buf);
	std::size_t				lineReturnLoc;
	std::string				messageToPrint;
	while (rawMessage.length())
	{
		lineReturnLoc = rawMessage.find("\r\n", 0);
		if (lineReturnLoc == rawMessage.npos)
			lineReturnLoc = rawMessage.length();
		messageToPrint = rawMessage.substr(0, lineReturnLoc);
		if (lineReturnLoc != rawMessage.length())
			lineReturnLoc += 2;
		rawMessage = rawMessage.replace(0, lineReturnLoc, "");
		Logger(Output::DEBUG) << prefix << user.getNickname() << ": " << messageToPrint;
	}
}
