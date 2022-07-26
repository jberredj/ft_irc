/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:19:33 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/26 22:32:12 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "User.hpp"
# include "ChannelMode.hpp"
# include <map>
# include <vector>
# include <string>
# include "types/Nullptr_t.hpp"

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
	// void	setChannelModes(std::string mode);
	bool	setTopic(std::string topic);
	bool	addUser(User *user);
	bool	removeUser(User *user);
	void	broadcastMessage(std::string message, User *sender = ft::null_ptr);
	bool	isBanned(User *user);
	void	setInvite(bool invite);
	bool	getInvite(void) const;
	bool	isInvited(User* user);
	bool	isAlive(void) const;
	bool	isOperator(User *user);
	bool	isMember(User *user);
	bool	hasTopic(void);
	bool	inviteUser(User* user);


	std::string	getName(void) const;
	int			getUserLimit(void) const;
	std::string	getUserMode(User* user);
	std::string	getTopic(void) const;
	int			getNbrMember(void) const;
	
	std::vector<User*>	getMembers(void) const;
	ChannelMode	getChannelMode(void) const;

private:
	bool							_isAlive;
	std::string						_name;
	int								_userLimit;
	int								_nbrMember;
	ChannelMode						_modes;
	std::vector<User*>				_members;
	bool							_inviteOnly;
	std::vector<User*>				_inviteList;
	std::vector<User*>				_banList;
	std::map<User*, std::string>	_userModes;
	time_t							_topicSetAt;
	std::string						_topic;

	bool	_banUser(User* user);
	bool	_unbanUser(User* user);
	bool	_revokeInviteUser(User* user);
};

#endif
