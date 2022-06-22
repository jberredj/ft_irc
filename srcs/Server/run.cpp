/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:34:06 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/22 18:55:28 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <poll.h>
#include <sys/fcntl.h>
#include "Server.hpp"
#include "User.hpp"
#include "Logger.hpp"

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// General methods and functions
void	Server::run(void)
{
	while (_running)
	{
		int	pollResult = poll(static_cast<struct pollfd*>(&(*_pollfds.begin())),
							_pollfds.size(), 0);
		if (pollResult > 0)
		{
			if (_pollfds[0].revents & POLLIN)
				_newIncommingSocket();
			_pollIO();
		}
		_treatUserMessages();
		_pruneUser();
		_pruneChannel();
		if (Server::_sigInt)
		{
			_running = false;
			std::cout << "\b\b";
			Logger(Output::WARN) << "Server terminated by Ctrl+C";
		}
	}
}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

void	Server::_treatUserMessages(void)
{
	for(std::map<int, User*>::iterator ctx_it = _usersMap.begin();
		ctx_it != _usersMap.end(); ctx_it++)
	{
		// User::Status	state = (*ctx_it).second->getStatus();
		try 
		{
			(*ctx_it).second->execCommandQueue();
		}
		catch (const std::exception& e)
		{
			Logger(Output::FATAL) << e.what();
			_running = false;
			_exitCode = 1;
		}
	}	
}