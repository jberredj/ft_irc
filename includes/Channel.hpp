/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:19:33 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 01:08:43 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "User.hpp"
# include <map>
# include <vector>
# include <string>

class Server;

class Channel
{
public:
	Channel(void);
	Channel(const Channel &src);
	Channel(std::string name);
	~Channel(void);

	Channel	&operator=(const Channel &rhs);

	bool	setUserLimit(int limit);
	bool	setUserMode(std::string mode, User* user);
	void	setChannelMode(std::string mode);
	bool	addUser(User *user);
	bool	removeUser(User *user);
	void	broadcastMessage(std::string message);
	bool	isBanned(User *user);
	void	setInvite(bool invite);
	bool	getInvite(void) const;
	bool	isInvited(User* user);

	bool	isAlive(void) const;
	std::string	getName(void) const;
	int			getUserLimit(void) const;
	std::string	getUserMode(User* user);
	std::string	getChannelMode(void) const;
private:
	bool							_isAlive;
	std::string						_name;
	int								_userLimit;
	int								_nbrMember;
	std::string						_mode;
	std::vector<User*>				_member;
	bool							_inviteOnly;
	std::vector<User*>				_inviteList;
	std::vector<User*>				_banList;
	std::map<User*, std::string>	_userModes;

	bool	_banUser(User* user);
	bool	_unbanUser(User* user);
	bool	_inviteUser(User* user);
	bool	_revokeInviteUser(User* user);
};



#endif