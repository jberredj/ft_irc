/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:15:14 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/14 23:41:10 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP
# include "User.hpp"
# include <map>
# include <vector>
# include <fstream>

class IrcServ
{
private:
	std::string					_password;
	bool						_running;
	static bool					_sigInt;
	int							_serverSocket;
	std::vector<struct pollfd>	_pollfds;
	std::map<int, User>			_users;
	int							_portInstanceLock;
	std::vector<std::string>	_nicksInUse;

								IrcServ(void);
	void						_preparePollfds(void);
	static void					_SigIntHandler(int signum);
	int							_CreateServerSocket(char *port);
	void						_logRawMessage(char *buf, User &user);
	void						_uniqueInstanceOnPort(char *port);
public:
								IrcServ(int ac, char **av);
								IrcServ(const IrcServ &src);
								~IrcServ(void);

	IrcServ						&operator=(const IrcServ &rhs);
	int							acceptConnection(int socketfd);
	void						run(void);
};

#endif