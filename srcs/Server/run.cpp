/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:34:06 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 18:33:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include <vector>
#include <poll.h>
#include <sys/fcntl.h>
#include "Server.hpp"

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// General methods and functions
void	Server::run(void)
{
	while (_running)
	{
		// printf("useClient => %d\n", useClient);
		int	pollResult = poll(static_cast<struct pollfd*>(&(*_pollfds.begin())),
							_pollfds.size(), 5000);
		if (pollResult > 0)
		{
			if (_pollfds[0].revents & POLLIN)
				_newIncommingSocket();
			_pollIO();
			_treatUserMessages();
			_pruneUser();
		}
		if (Server::_sigInt)
		{
			_running = false;
			std::cout << "\b\b";
			Logger(Output::WARN) << "Server terminated by Ctrl+C";
		}
	}
	close(_serverSocket);
}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

void	Server::_treatUserMessages(void)
{
	for(std::map<int, User>::iterator ctx_it = _users.begin();
		ctx_it != _users.end(); ctx_it++)
	{
		(*ctx_it).second.execCommandQueue();
	}	
}