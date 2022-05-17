/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInteractions.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:56:23 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/17 19:40:02 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <algorithm>
#include "User.hpp"
#include "Server.hpp"

void	Server::_addNewUser(int socketToBind, struct sockaddr_in cliAddr)
{
	User*	new_user = new User(&_password);
	new_user->setServaddr(inet_ntoa(cliAddr.sin_addr));
	new_user->setStatus(User::PASSWORD);
	_usersMap.insert(std::make_pair(socketToBind, new_user));
	_users.push_back(new_user);
}

void	Server::_pruneUser(void)
{
	std::vector<std::vector<struct pollfd>::iterator>	toErase;
	
	for (std::vector<struct pollfd>::iterator it = _pollfds.begin() + 1;
		it != _pollfds.end(); it++)
	{
		User*	ctx = _usersMap[(*it).fd];
		if (ctx->getStatus() == User::DELETE)
		{
			_usersMap.erase(_usersMap.find((*it).fd));
			close((*it).fd);
			Logger(Output::DEBUG) << "Close connection on socket: " << (*it).fd;
			delete ctx;
			_users.erase(std::find(_users.begin(), _users.end(), ctx));
			toErase.push_back(it);
		}
	}
	for (std::vector<std::vector<struct pollfd>::iterator>::iterator 
		it = toErase.begin(); it != toErase.end(); it++)
			_pollfds.erase(*it);
}