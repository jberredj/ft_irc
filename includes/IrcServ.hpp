/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:15:14 by jberredj          #+#    #+#             */
/*   Updated: 2022/04/28 17:26:46 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP

class IrcServ
{
private:
	bool		_running;
	static bool	_SigInt;
	int			server_socket;

	static void	_SigIntHandler(int signum);
				IrcServ(void);
	int			_CreateServerSocket(char *port);
public:
				IrcServ(int ac, char **av);
				IrcServ(const IrcServ &src);
				~IrcServ(void);

	IrcServ		&operator=(const IrcServ &rhs);

	void		run(void);
};

#endif