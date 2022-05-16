/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInteractions.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:56:23 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 20:43:13 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <algorithm>
#include "Server.hpp"

void	Server::_addNewUser(int socketToBind, struct sockaddr_in cliAddr)
{
	User	new_user(&_password, &_nicksInUse);
	new_user.setServaddr(inet_ntoa(cliAddr.sin_addr));
	new_user.setStatus(User::PASSWORD);
	_nicksInUse.push_back("-");
	_users.insert(std::make_pair(socketToBind, new_user));
}

void	Server::_pruneUser(void)
{
	std::vector<std::vector<struct pollfd>::iterator>	toErase;
	
	for (std::vector<struct pollfd>::iterator it = _pollfds.begin();
		it != _pollfds.end(); it++)
	{
		User&	ctx = _users[(*it).fd];
		if (ctx.getStatus() == User::DELETE)
		{
			std::vector<std::string>::iterator nickIt;
			nickIt = std::find(_nicksInUse.begin(), _nicksInUse.end(),
						ctx.getNickname());
			if (nickIt == _nicksInUse.end())
			{
				Logger(Output::WARN) << "Nick \""
					<< ctx.getNickname() << "\" not found";
			}
			else
				_nicksInUse.erase(nickIt);
			_users.erase(_users.find((*it).fd));
			close((*it).fd);
			Logger(Output::DEBUG) << "Close connection on socket: " << (*it).fd;
			toErase.push_back(it);
		}
	}
	for (std::vector<std::vector<struct pollfd>::iterator>::iterator 
		it = toErase.begin(); it != toErase.end(); it++)
			_pollfds.erase(*it);
}