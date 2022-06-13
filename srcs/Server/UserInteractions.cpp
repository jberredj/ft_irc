/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInteractions.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:56:23 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/13 19:54:59 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <algorithm>
#include "types/Nullptr_t.hpp"
#include "User.hpp"
#include "Logger.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

User*	Server::getUser(std::string nickname)
{
	_nickToFind = nickname;
	std::vector<User *>::iterator find;

	find = std::find_if(_users.begin(), _users.end(), _nickFinder);
	_nickToFind.clear();
	if (find == _users.end())
		return ft::null_ptr;
	return (*find);	
}

std::vector<User*>*	Server::getUsers(void) {return &_users;}

User*	Server::getOldUser(std::string nickname)
{
	_nickToFind = nickname;
	std::vector<User *>::iterator find;

	find = std::find_if(_oldUsers.begin(), _oldUsers.end(), _nickFinder);
	_nickToFind.clear();
	if (find == _oldUsers.end())
		return ft::null_ptr;
	return (*find);	
}

std::vector<User*>*	Server::getOldUsers(void) {return &_oldUsers;}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

void	Server::_addNewUser(int socketToBind, struct sockaddr_in cliAddr)
{
	
	User*	new_user = new User(&_password);
	new_user->setHostname(inet_ntoa(cliAddr.sin_addr));	
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
		switch (ctx->getStatus())
		{
		case User::DELETE:
			close((*it).fd);
			Logger(Output::DEBUG) << "Close connection on socket: " << (*it).fd;
		case User::OFFLINE:
			_usersMap.erase(_usersMap.find((*it).fd));
			_users.erase(std::find(_users.begin(), _users.end(), ctx));
			toErase.push_back(it);
			_oldUsers.push_back(ctx);
			break;
		default:
			break;
		}
	}
	for (std::vector<std::vector<struct pollfd>::iterator>::iterator 
		it = toErase.begin(); it != toErase.end(); it++)
			_pollfds.erase(*it);
}