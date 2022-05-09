/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:28:19 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/09 19:56:49 by jberredj         ###   ########.fr       */
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

bool IrcServ::_SigInt = false;

IrcServ::IrcServ(void)
{
    _prepare_pollfds();
}

void	IrcServ::_SigIntHandler(int signum)
{
	(void)signum;
	IrcServ::_SigInt = true;
}

int IrcServ::_CreateServerSocket(char *port)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    Logger::info("Requested port: " + std::string(port));
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

void IrcServ::_prepare_pollfds(void)
{
    struct pollfd new_socket;
    new_socket.fd = 0;
    new_socket.events = POLLIN | POLLPRI;
    new_socket.revents = 0;
    pollfds.push_back(new_socket);
}

IrcServ::IrcServ(int ac, char **av)
{
	signal(SIGINT, IrcServ::_SigIntHandler);
    _prepare_pollfds();
	_server_socket = _CreateServerSocket((char *)av[1]);
    pollfds[0].fd = _server_socket;
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
}

IrcServ	&IrcServ::operator=(const IrcServ &rhs)
{
	*this = rhs;
	return *this;
}

int			IrcServ::accept_connection(int socketfd)
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
    User new_user(inet_ntoa(cliaddr.sin_addr));
    _users.insert(std::make_pair(client_socket, new_user));
    return client_socket;
}




void	IrcServ::run(void)
{
	struct pollfd new_socket;
	while (_running)
	{
		// printf("useClient => %d\n", useClient);
        int pollResult = poll(static_cast<struct pollfd*>(&(*pollfds.begin())), pollfds.size(), 5000);
        if (pollResult > 0)
        {
            if (pollfds[0].revents & POLLIN)
            {
                int client_socket = accept_connection(_server_socket);
                new_socket.fd = client_socket;
                new_socket.events = POLLIN | POLLPRI;
                pollfds.push_back(new_socket);
            }
            std::vector<std::vector<struct pollfd>::iterator> to_close;
            for (std::vector<struct pollfd>::iterator it = pollfds.begin() + 1 ; it != pollfds.end(); it++)
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
                        Logger::info("From client: " + std::string(buf));
                    }
                }
            }
            for (std::vector<std::vector<struct pollfd>::iterator>::iterator it = to_close.begin(); it != to_close.end(); it++)
            {
                pollfds.erase(*it);
            }
            to_close.clear();
        }
		if (IrcServ::_SigInt)
		{
			_running = false;
            std::cout << "\b\b";
			Logger::warn("Server terminated by Ctrl+C");
		}
	}
	close(_server_socket);
}