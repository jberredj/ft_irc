/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:28:19 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/10 15:10:11 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "IrcServ.hpp"
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <poll.h>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <sys/fcntl.h>
#include <sstream>
#include "Logger.hpp"

bool IrcServ::_sigInt = false;

IrcServ::IrcServ(void)
{
	_preparePollfds();
}

void	IrcServ::_SigIntHandler(int signum)
{
	(void)signum;
	IrcServ::_sigInt = true;
}

int IrcServ::_CreateServerSocket(char *port)
{
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bindResult = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr));
	if (bindResult == -1)
		throw(std::runtime_error("bind() failed"));

	int listenResult = listen(server_socket, 5);
	if (listenResult == -1)
		throw(std::runtime_error("listen() failed"));

	Logger::info("Server started successfully on port: " + std::string(port));
	return server_socket;
}

void IrcServ::_preparePollfds(void)
{
	struct pollfd new_socket;
	new_socket.fd = 0;
	new_socket.events = POLLIN | POLLPRI;
	new_socket.revents = 0;
	_pollfds.push_back(new_socket);
}

void	IrcServ::_uniqueInstanceOnPort(char *port)
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
		throw(std::runtime_error("Another instance of ircserv is running on port " +  std::string(port)));
}

IrcServ::IrcServ(int ac, char **av)
{
	if (ac != 3)
	{
		throw(std::runtime_error("usage: " + std::string(av[0]) + " <port> <password>"));
	}
	Logger::info("Requested port: " + std::string((char *)av[1]));
	_uniqueInstanceOnPort((char *)av[1]);
	signal(SIGINT, IrcServ::_SigIntHandler);
	_preparePollfds();
	_serverSocket = _CreateServerSocket((char *)av[1]);
	_pollfds[0].fd = _serverSocket;
	(void)ac;
	(void)av;
	_running = true;
}

IrcServ::IrcServ(const IrcServ &src)
{
	*this = src;
}

IrcServ::~IrcServ(void)
{
	close(_portInstanceLock);
}

IrcServ	&IrcServ::operator=(const IrcServ &rhs)
{
	*this = rhs;
	return *this;
}

int			IrcServ::acceptConnection(int socketfd)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	int client_socket = accept(socketfd, (struct sockaddr *)&cliaddr, &addrlen);

	if (client_socket == -1)
	{
		Logger::error("Fail accepting connection");
		return -1;
	}
	int flags = fcntl(client_socket, F_GETFL);
	if (flags == -1)
	{
		Logger::error("Could not get socket flags");
		return -1;
	}
	if (fcntl(client_socket, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		Logger::error("Could not set socket flags");
		return -1;
	}
	std::ostringstream socket_nbr;
	socket_nbr << client_socket;
	Logger::debug("New connection from " + std::string(inet_ntoa(cliaddr.sin_addr)) + " on socket : " + socket_nbr.str());
	// User new_user(inet_ntoa(cliaddr.sin_addr));
	User new_user;
	new_user.setServaddr(inet_ntoa(cliaddr.sin_addr));
	new_user.setUstatus(PASSWORD);
	_users.insert(std::make_pair(client_socket, new_user));
	return client_socket;
}


void	IrcServ::_logRawMessage(char *buf, User &user)
{
	std::string 			rawMessage(buf);
	std::string::iterator	lineReturnLoc = rawMessage.begin() + rawMessage.find('\n', 0);
	rawMessage = rawMessage.replace(lineReturnLoc, rawMessage.end(), "");
	Logger::info("From " + user.getUsername() + ": " + rawMessage);
}

void	IrcServ::run(void)
{
	struct pollfd new_socket;
	while (_running)
	{
		// printf("useClient => %d\n", useClient);
		int pollResult = poll(static_cast<struct pollfd*>(&(*_pollfds.begin())), _pollfds.size(), 5000);
		if (pollResult > 0)
		{
			if (_pollfds[0].revents & POLLIN)
			{
				int client_socket = acceptConnection(_serverSocket);
				new_socket.fd = client_socket;
				new_socket.events = POLLIN | POLLPRI;
				_pollfds.push_back(new_socket);
			}
			std::vector<std::vector<struct pollfd>::iterator> to_close;
			for (std::vector<struct pollfd>::iterator it = _pollfds.begin() + 1 ; it != _pollfds.end(); it++)
			{
				if ((*it).fd > 0 && (*it).revents & POLLIN)
				{
					char buf[512];
					int bufSize = read((*it).fd, buf, 512 - 1);
					if (bufSize <= 0)
					{
						std::ostringstream socket_nbr;

						socket_nbr << (*it).fd;
						close((*it).fd);
						to_close.push_back(it);
						Logger::debug("Close connection on socket : " + socket_nbr.str());
					}
					else
					{
						buf[bufSize] = '\0';
						_logRawMessage(buf, _users[(*it).fd]);
					}
				}
			}
			for (std::vector<std::vector<struct pollfd>::iterator>::iterator it = to_close.begin(); it != to_close.end(); it++)
			{
				struct pollfd userdel;
				userdel = *(*it);
				_users.erase(userdel.fd);
				_pollfds.erase(*it);
			}
			to_close.clear();
		}
		if (IrcServ::_sigInt)
		{
			_running = false;
			std::cout << "\b\b";
			Logger::warn("Server terminated by Ctrl+C");
		}
	}
	close(_serverSocket);
}