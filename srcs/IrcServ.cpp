/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:28:19 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/03 23:49:29 by jberredj         ###   ########.fr       */
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

bool IrcServ::_SigInt = false;

IrcServ::IrcServ(void) {} // Default constructor is private and unused

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
	std::cout << addr.sin_port << " " << atoi(port) << " " << port << std::endl;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int bindResult = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr));
    if (bindResult == -1)
    {
		// throw something
        // perror("bindResult");
		throw(std::runtime_error("bind failed"));
    }

    int listenResult = listen(server_socket, 5);
    if (listenResult == -1)
    {
		throw(std::runtime_error("listen failed"));
		// throw something
        // perror("listenResult");
    }
    std::cout << "Server started" << std::endl;
    return server_socket;
}

IrcServ::IrcServ(int ac, char **av) 
{
	signal(SIGINT, IrcServ::_SigIntHandler);
	server_socket = _CreateServerSocket((char *)av[1]);
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

#define MAX_CLIENTS 10

void	IrcServ::run(void)
{
    std::vector<struct pollfd> pollfds;
    struct pollfd new_socket;
    new_socket.fd = server_socket;
    new_socket.events = POLLIN | POLLPRI;;
    pollfds.push_back(new_socket);
    int useClient = 0;
	
	while (_running)
	{
		// printf("useClient => %d\n", useClient);
        int pollResult = poll(static_cast<struct pollfd*>(&(*pollfds.begin())), pollfds.size() + 1, 5000);
        if (pollResult > 0)
        {
            if (pollfds[0].revents & POLLIN)
            {
                struct sockaddr_in cliaddr;
                socklen_t addrlen = sizeof(cliaddr);
                
                int client_socket = accept(server_socket, (struct sockaddr *)&cliaddr, &addrlen);
                std::cout << "accept success " << inet_ntoa(cliaddr.sin_addr) << " fd: " << client_socket << std::endl;
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
                        close((*it).fd);
                        to_close.push_back(it);
                        std::cout << "close connection" << std::endl;
                    }
                    else
                    {
                        buf[bufSize] = '\0';
                        std::cout << "From client: " << buf << std::endl;
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
			std::cout << "End by SIGINT" << std::endl;
		}
	}
	close(server_socket);
}