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
# include <map>
# include <vector>
# include <fstream>
# ifndef IRC_MESSAGE_LEN
#  define IRC_MESSAGE_LEN 512
# endif


class Server
{
public:
	// Constructors and destructor
			Server(int ac, char** av);
			Server(const Server& src);
			~Server(void);

	// Operators
	Server&	operator=(const Server& rhs);

	// Getters
	short	getExitCode(void) const;

	// General methods and functions
	void	run(void);

private:
	static bool					_sigInt;
	short						_exitCode;
	std::string					_password;
	bool						_running;
	int							_serverSocket;
	std::vector<struct pollfd>	_pollfds;
	std::map<int, User>			_users;
	int							_portInstanceLock;
	std::vector<std::string>	_nicksInUse;

	// Constructors
								Server(void);

	// Run loop methods and functions
	void						_treatUserMessages(void);

	// General methods and functions
	static void					_SigIntHandler(int signum);
	void						_logRawMessage(char* buf, User& user);
	void						_uniqueInstanceOnPort(char* port);

	// SocketIO methods and functions
	int							_createServerSocket(char* port);
	void						_preparePollfds(void);
	int							_acceptConnection(int socketfd);
	void						_newIncommingSocket(void);
	void						_pollIO(void);
	void						_socketReadInput(
									std::vector<struct pollfd>::iterator it);
	void						_socketWrite(
									std::vector<struct pollfd>::iterator it);

	// User interactions methods and functions
	void 						_addNewUser(int socketToBind, 
									struct sockaddr_in cliAddr);
	void						_pruneUser(void);
};

#endif