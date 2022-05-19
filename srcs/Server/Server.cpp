/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:28:19 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/19 12:43:41 by jberredj         ###   ########.fr       */
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

#include "Logger.hpp"
#include <poll.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// Constructors and destructor
Server::Server(int ac, char** av):
	_exitCode(0)
{
	if (ac != 3)
	{
		throw(std::runtime_error("usage: " + std::string(av[0]) +
			" <port> <password>"));
	}
	Logger(Output::INFO) << "Requested port: " << av[1];
	_uniqueInstanceOnPort((char*)av[1]);
	signal(SIGINT, Server::_SigIntHandler);
	_preparePollfds();
	_serverSocket = _createServerSocket((char*)av[1]);
	_pollfds[0].fd = _serverSocket;
	_password = av[2];
	_running = true;
}

Server::Server(const Server &src)
{
	Logger(Output::WARN) << "Incomplete copy constructor for Server";
	*this = src;
}

Server::~Server(void)
{
	Logger(Output::WARN) << "HANDLE FREE USER";
	for(std::vector<struct pollfd>::iterator it = _pollfds.begin();
		it != _pollfds.end(); it++)
			close((*it).fd);	
	close(_serverSocket);
	close(_portInstanceLock);
}

// Getters
short	Server::getExitCode(void) const {return _exitCode;}

// Operators
Server&	Server::operator=(const Server& rhs)
{
	Logger(Output::WARN) << "Incomplete assignement operator for Server";
	// *this = rhs;
	(void)rhs;
	return *this;
}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

// Static variable initialisation
bool Server::_sigInt = false;

// Constructors
Server::Server(void)
{
	_preparePollfds();
}

// General methods and functions
void	Server::_SigIntHandler(int signum)
{
	(void)signum;
	Server::_sigInt = true;
}

void	Server::_logRawMessage(char *buf, User &user)
{
	std::string				rawMessage(buf);
	std::string::iterator	lineReturnLoc = rawMessage.begin() + 
												rawMessage.find('\n', 0);

	rawMessage = rawMessage.replace(lineReturnLoc, rawMessage.end(), "");
	Logger(Output::INFO) << "From " << user.getUsername() << ": " << rawMessage;
}

void	Server::_uniqueInstanceOnPort(char *port)
{
	struct flock fl;
	std::string	filename("/tmp/ft_ircserv_" + std::string(port));
	_portInstanceLock = open(filename.c_str(), O_WRONLY | O_CREAT, 0600);
	if (_portInstanceLock == -1)
		throw(std::runtime_error("Can't open lock file"));
	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	if (fcntl(_portInstanceLock, F_SETLK, &fl) < 0)
		throw(std::runtime_error("Another instance of ircserv "
			"is running on port " +  std::string(port)));
}


std::string	Server::_nickToFind;

bool	Server::_nickFinder(User *user)
{
	if (user)
	{
		if (user->getNickname() == _nickToFind)
			return true;
	}
	return false;
}
