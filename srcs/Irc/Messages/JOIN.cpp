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
	while ((channel = getNextChannel(channelList, command))) // TODO - Infinite loop ?
	{
		Logger(Output::WARN) << "NO CHECK ARE IMPLEMENTED TO CHECK IF USER IS AUTHORIZED TO JOIN";
		// TODO: ADD Check if User can join
		if (channel->addUser(&command.getInvoker()))
		{
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
}
