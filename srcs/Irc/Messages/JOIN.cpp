/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:21:35 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/26 23:53:53 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"
#include "typedefs.hpp"

void	JOIN(Command &command)
{
	if (needMoreParams(command, 1))
		return;
	std::string	channelList = command.getParameters()[0];
	Channel*	channel = ft::null_ptr;
	while ((channel = getNextChannel(channelList, command)))
	{
		User &user = command.getInvoker();
		if (channel->hasMode(ChannelMode::CMODE_I) && !channel->isInvited(&user)) {
			strVec args;
			args.push_back(channel->getName());
			command.replyToInvoker(473, args);
			continue;
		}
		if (channel->hasMode(ChannelMode::CMODE_L) && channel->isFull()) {
			strVec args;
			args.push_back(channel->getName());
			command.replyToInvoker(471, args);
			continue;
		}
		if (!channel->addUser(&command.getInvoker()))
			continue;

		channel->broadcastMessage(":" + command.getInvoker().getPrefix() + " JOIN :" + channel->getName());
		if (channel->hasTopic())
		{
			strVec	args;
			args.push_back(channel->getName());
			args.push_back(channel->getTopic());
			command.replyToInvoker(332, args);
		}
		listChannelMembers(command, channel);
	}
}
