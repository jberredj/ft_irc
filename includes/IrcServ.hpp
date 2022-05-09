/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:15:14 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/09 19:50:29 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP
# include "User.hpp"
# include <map>
# include <vector>

class IrcServ
{
private:
	bool						_running;
	static bool					_SigInt;
	int							_server_socket;
	std::vector<struct pollfd>	pollfds;
	std::map<int, User>			_users;

								IrcServ(void);
	void						_prepare_pollfds(void);
	static void					_SigIntHandler(int signum);
	int							_CreateServerSocket(char *port);
public:
				IrcServ(int ac, char **av);
				IrcServ(const IrcServ &src);
				~IrcServ(void);

	IrcServ		&operator=(const IrcServ &rhs);
	int			accept_connection(int socketfd);
	void		run(void);
};

#endif