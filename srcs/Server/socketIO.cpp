/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketIO.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:37:21 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/23 00:08:04 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <cstdlib>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <poll.h>
#include "Server.hpp"
#include "IrcMessages.hpp"

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

int	Server::_createServerSocket(char* port)
{
	int					server_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int 				bindResult = bind(server_socket,
										(struct sockaddr*)&addr, sizeof(addr));

	if (bindResult == -1)
		throw(std::runtime_error("bind() failed"));
	int 				listenResult = listen(server_socket, 5);

	if (listenResult == -1)
		throw(std::runtime_error("listen() failed"));
	Logger(Output::INFO) << "Server started successfully on port: "
		<< std::string(port);
	return server_socket;
}

void	Server::_preparePollfds(void)
{
	struct pollfd	new_socket;
	new_socket.fd = 0;
	new_socket.events = POLLIN | POLLPRI;
	new_socket.revents = 0;
	_pollfds.push_back(new_socket);
}

int	Server::_acceptConnection(int socketfd)
{
	struct sockaddr_in	cliaddr;
	socklen_t 			addrlen = sizeof(cliaddr);
	int 				client_socket = accept(socketfd,
										(struct sockaddr*)&cliaddr, &addrlen);

	if (client_socket == -1)
	{
		Logger(Output::ERROR) << "Fail accepting connection";
		return -1;
	}
	int 				flags = fcntl(client_socket, F_GETFL);
	
	if (flags == -1)
	{
		Logger(Output::ERROR) << "Could not get socket flags";
		return -1;
	}
	if (fcntl(client_socket, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		Logger(Output::ERROR) <<  "Could not set socket flags";
		return -1;
	}
	Logger(Output::DEBUG) << "New connection from " 
		<< inet_ntoa(cliaddr.sin_addr) << " on socket : " << client_socket;
	_addNewUser(client_socket, cliaddr);
	return client_socket;
}

void	Server::_newIncommingSocket(void)
{
	struct pollfd	new_socket;
	int client_socket = _acceptConnection(_serverSocket);
	new_socket.fd = client_socket;
	new_socket.events = POLLIN | POLLPRI | POLLOUT;
	new_socket.revents = 0;
	_pollfds.push_back(new_socket);
}

void	Server::_pollIO(void)
{
	for (std::vector<struct pollfd>::iterator it = _pollfds.begin() + 1;
		it != _pollfds.end(); it++)
	{
		if ((*it).fd > 0 && (*it).revents & POLLIN)
			_socketReadInput(it);
		else if ((*it).fd > 0 && (*it).revents & POLLOUT)
			_socketWrite(it);
	}
}

void	Server::_socketReadInput(std::vector<struct pollfd>::iterator it)
{
	char	buf[IRC_MESSAGE_LEN + 1];
	int		bufSize = read((*it).fd, buf, IRC_MESSAGE_LEN);
	if (bufSize <= 0)
		_usersMap[(*it).fd]->setStatus(User::DELETE);
	else
	{
		User*		ctx = _usersMap[(*it).fd];

		buf[bufSize] = '\0';
		_logRawMessage(buf, *_usersMap[(*it).fd], "From ");
		std::string	rawMessage(ctx->getCommandBuf());
		ctx->clearCommandBuff();
		rawMessage += buf;
		while (!rawMessage.empty())
		{
			std::size_t	endMessageLocation = rawMessage.find("\n", 0);
			std::size_t	endOffset = 1;
			
			if (endMessageLocation && endMessageLocation != rawMessage.npos 
				&& rawMessage.at(endMessageLocation - 1) != '\r')
			{
				endOffset = 0;
				Logger(Output::WARN) << "Incorrect EOL char";
			}
			if (endMessageLocation == rawMessage.npos)
			{
				ctx->setCommandBuf(rawMessage);
				break;
			}
			Command	newCommand(ctx, rawMessage.substr(0, 
				endMessageLocation - endOffset), this);
			ctx->addCommand(newCommand);
			rawMessage.erase(rawMessage.begin(), rawMessage.begin()
				+ endMessageLocation + 1);
		}
	}
}

void	Server::_socketWrite(std::vector<struct pollfd>::iterator it)
{
	if (_usersMap[(*it).fd] && _usersMap[(*it).fd]->repliesAvalaible())
	{
		std::string	payload = _usersMap[(*it).fd]->getReplies();
		const char	*rawBuf = payload.c_str();
		_logRawMessage((char *)rawBuf, *_usersMap[(*it).fd], "Sending to ");
		write((*it).fd, payload.c_str(), payload.size());
		if (_usersMap[(*it).fd]->getStatus() == User::OFFLINE && !_usersMap[(*it).fd]->repliesAvalaible())
			_usersMap[(*it).fd]->setStatus(User::DELETE);
	}
}