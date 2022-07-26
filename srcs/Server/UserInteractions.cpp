/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInteractions.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:56:23 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/18 19:50:27 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <algorithm>
#include "typedefs.hpp"
#include "User.hpp"
#include "Logger.hpp"
#include "Server.hpp"

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

User*	Server::getUser(std::string nickname) {
	std::vector<User *>::iterator user = _users.begin();

	while (user != _users.end()) {
		if ((*user)->getNickname() == nickname)
			return *user;
		user++;
	}
	return ft::null_ptr;
}

User*	Server::getUserFromName(std::string username) {
	std::vector<User *>::iterator user = _users.begin();

	while (user != _users.end()) {
		if ((*user)->getUsername() == username)
			return *user;
		user++;
	}
	return ft::null_ptr;
}

std::vector<User*>*	Server::getUsers(void) {return &_users;}

User*	Server::getOldUser(std::string nickname) {
	std::vector<User *>::iterator user = _oldUsers.begin();

	while (user != _oldUsers.end()) {
		if ((*user)->getNickname() == nickname)
			return *user;
		user++;
	}
	return ft::null_ptr;
}

std::vector<User*>*	Server::getOldUsers(void) {return &_oldUsers;}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

void	Server::_addNewUser(int socketToBind, struct sockaddr_in cliAddr) {
	
	User*	new_user = new User();
	new_user->setHostname(inet_ntoa(cliAddr.sin_addr));	
	new_user->setStatus(User::PASSWORD);
	_usersMap.insert(std::make_pair(socketToBind, new_user));
	_users.push_back(new_user);
}



void	Server::_tryUnregisterUser(User *user, int socket) {
	if (!user->repliesAvalaible()) {
		std::vector<Channel*> userChannels = user->getChannels();
		for (channelIterator it = userChannels.begin(); it != userChannels.end(); it++)
			(*it)->removeUser(user);
		user->clearChannels();
		_usersMap.erase(_usersMap.find(socket));
		_users.erase(std::find(_users.begin(), _users.end(), user));
		_oldUsers.push_back(user);
	}
}

void	Server::_closeClient(User *user, int socket)
{
	close(socket);
	user->clearReplies();
	user->clearCommandQueue();
	user->clearCommandBuff();
	Logger(Output::DEBUG) << "Close connection on socket: " << socket;
}

void	Server::_pruneUser(void) {
	std::vector<pollfdsIterator>	closedConnector;
	
	for (pollfdsIterator connector = _pollfds.begin() + 1; connector != _pollfds.end(); connector++) {
		int		socket = (*connector).fd;
		User*	user = _usersMap[socket];
		if (!user)
			continue;

		switch (user->getStatus()) {
		case User::DELETE:
			_closeClient(user, socket);
			closedConnector.push_back(connector);
		case User::OFFLINE:
			(*connector).events = POLLOUT;
			_tryUnregisterUser(user, socket);
			break;
		default:
			break;
		}
	}
	for (std::vector<pollfdsIterator>::iterator it = closedConnector.begin(); it != closedConnector.end(); it++)
			_pollfds.erase(*it);
}