/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:15:14 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 16:01:48 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP
# include "User.hpp"
# include "Channel.hpp"
# include <string>
# include <map>
# include <vector>
# include <fstream>

class Server
{
public:
	// Constructors and destructor
					Server(int ac, char** av);
					Server(const Server& src);
					~Server(void);

	// Operators
	Server&			operator=(const Server& rhs);

	// Getters
	short			getExitCode(void) const;

	// Channel Interaction methods and functions

	void			addChannel(Channel *channel);
	Channel*		getChannel(std::string name);
	std::map<std::string, Channel*>*	getChannels(void);

	// General methods and functions
	void			run(void);
	std::string		getServerName(void) const;
	void			setServerName(std::string serverName);
	std::string		getPassword(void) const;

	// User interactions methods and function
	User*				getUser(std::string nickname);
	User*				getUserFromName(std::string username);
	std::vector<User*>*	getUsers(void);
	User*				getOldUser(std::string nickname);
	std::vector<User*>*	getOldUsers(void);

private:
	static bool					_sigInt;
	short						_exitCode;
	std::string					_password;
	bool						_running;
	int							_serverSocket;
	std::vector<struct pollfd>	_pollfds;
	std::map<int, User*>		_usersMap;
	int							_portInstanceLock;
	std::vector<User *>			_users;
	std::vector<User *>			_oldUsers;
	std::string					_serverName;

	std::map<std::string, Channel*>	_channels;

	// Constructors
				Server(void);

	// Channel Interaction methods and functions
	void		_pruneChannel(void);

	// Run loop methods and functions
	void		_checkUserTimedOut(User* user);
	void		_treatUserMessages(void);

	// General methods and functions
	static void	_SigIntHandler(int signum);
	void		_logRawMessage(char* buf, User& user, std::string prefix);

	// SocketIO methods and functions
	int			_createServerSocket(char* port);
	void		_preparePollfds(void);
	int			_acceptConnection(int socketfd);
	void		_newIncommingSocket(void);
	void		_pollIO(void);
	void		_socketReadInput(std::vector<struct pollfd>::iterator it);
	void		_socketWrite(std::vector<struct pollfd>::iterator it);

	// User interactions methods and functions
	void 		_addNewUser(int socketToBind, struct sockaddr_in cliAddr);
	void		_pruneUser(void);
	void		_tryUnregisterUser(User *user, int socket);
	void		_closeClient(User *user, int socket);
};

#endif