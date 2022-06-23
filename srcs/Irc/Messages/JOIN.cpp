/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:21:35 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/23 17:05:12 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"
#include "typedefs.hpp"

void	_listChannelMembers(Command &command, Channel *channel)
{
	userVec		members = channel->getMembers();
	strVec		args;
	//:<server name> 353 <nickname> = <channel name> :[nickname [...]]\r\n
	std::size_t	minMessageLen = 1 + command.getServerName().length() + 5
		+ command.getInvoker().getNickname().length() + 3 + channel->getName().length() + 2;
	std::size_t	messageLen = minMessageLen;
	
	args.push_back(channel->getName());
	for(userVec::iterator it = members.begin(); it != members.end(); it++)
	{
		std::string	nickname;
		if (channel->isOperator(*it))
			nickname = "@";
		nickname += (*it)->getNickname();
		if (messageLen + nickname.length() + 1 > IRC_MESSAGE_LEN - 2)
		{
			command.replyToInvoker(353, args);
			args.erase(args.begin() + 1, args.end());
			messageLen = minMessageLen;
		}
		messageLen += nickname.length() + 1;
		args.push_back(nickname);
	}
	command.replyToInvoker(353, args);
	args.erase(args.begin() + 1, args.end());
	command.replyToInvoker(366, args);
}

void	JOIN(Command &command)
{
	if (needMoreParams(command, 1))
		return;
	std::string	channelList = command.getParameters()[0];
	Channel*	channel = ft::null_ptr;
	while ((channel = getNextChannel(channelList, command)))
	{
		// TODO: ADD Check if User can join
		if (channel->addUser(&command.getInvoker()))
		{
			channel->broadcastMessage(":" + command.getInvoker().getPrefix() + " JOIN :" + channel->getName());
			_listChannelMembers(command, channel);
		}
	}
}