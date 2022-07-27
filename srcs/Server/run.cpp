/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:34:06 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/27 01:57:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <poll.h>
#include <sys/fcntl.h>
#include "Server.hpp"
#include "typedefs.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "Logger.hpp"
#include "sstream"

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

void	Server::_checkUserTimedOut(User* user)
{
	int state = user->checkTimeOut();

	if (state == 1)
	{
		user->addReply("PING :" + this->getServerName());
		user->setExpectedPONG(this->getServerName());
	}
	else if (state == 2)
	{
		std::stringstream	nbrSec;
		nbrSec << ((std::time(ft::null_ptr) - user->getLastSeen()) / 2);
		Command	forceExit(user, "QUIT :Ping timeout:" + nbrSec.str() + " seconds", this);
		user->addCommand(forceExit);
		user->updateSeenTime(); // Force Update Seen time to avoid duplicate timeout
	}
}

void	Server::_treatUserMessages(void)
{
	for(userVec::iterator ctx_it = _users.begin();
		ctx_it != _users.end(); ctx_it++)
	{
		_checkUserTimedOut(*ctx_it);
		try 
		{
			(*ctx_it)->execCommandQueue();
		}
		catch (const std::exception& e)
		{
			Logger(Output::FATAL) << e.what();
			_running = false;
			_exitCode = 1;
		}
	}	
}