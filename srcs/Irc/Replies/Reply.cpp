/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:16:30 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/17 01:07:44 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "IrcMessages.hpp"

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// Constructors and destructor
Reply::Reply(void)
{
	_initRepliesMap();
}

Reply::Reply(const Reply &src)
{
	_initRepliesMap();
}

Reply::~Reply(void)
{
}

// Operators
Reply	&Reply::operator=(const Reply &rhs)
{
}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

// Init function
void	Reply::_initRepliesMap(void)
{
	if (_repliesMap.empty())
	{
		_repliesMap.insert(std::make_pair(1, RPL_WELCOME));
		_repliesMap.insert(std::make_pair(221, RPL_UMODEIS));
		_repliesMap.insert(std::make_pair(301, RPL_AWAY));
		_repliesMap.insert(std::make_pair(311, RPL_WHOISUSER));
		_repliesMap.insert(std::make_pair(312, RPL_WHOISSERVER));
		_repliesMap.insert(std::make_pair(313, RPL_WHOISOPERATOR));
		_repliesMap.insert(std::make_pair(317, RPL_WHOISIDLE));
		_repliesMap.insert(std::make_pair(318, RPL_ENDOFWHOIS));
		_repliesMap.insert(std::make_pair(319, RPL_WHOISCHANNELS));
		_repliesMap.insert(std::make_pair(321, RPL_LISTSTART));
		_repliesMap.insert(std::make_pair(322, RPL_LIST));
		_repliesMap.insert(std::make_pair(323, RPL_LISTEND));
		_repliesMap.insert(std::make_pair(331, RPL_NOTOPIC));
		_repliesMap.insert(std::make_pair(332, RPL_TOPIC));
		_repliesMap.insert(std::make_pair(341, RPL_INVITING));
		_repliesMap.insert(std::make_pair(353, RPL_NAMREPLY));
		_repliesMap.insert(std::make_pair(366, RPL_ENDOFNAMES));
		_repliesMap.insert(std::make_pair(381, RPL_YOUREOPER));
		_repliesMap.insert(std::make_pair(392, RPL_USERSSTART));
		_repliesMap.insert(std::make_pair(393, RPL_USERS));
		_repliesMap.insert(std::make_pair(394, RPL_ENDOFUSERS));
		_repliesMap.insert(std::make_pair(395, RPL_NOUSERS));
	}
}