/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 08:37:27 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/23 10:43:39 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "helpers.hpp"
#include "User.hpp"
#include "Command.hpp"

void	_partUser(Command& command, Channel *channel, std::string leaveMsg)
{
	User& invoker = command.getInvoker();
	if (channel)
	{
		if (channel->removeUser(&invoker))
		{
			std::string	message = ":" + invoker.getPrefix() + " PART " + channel->getName() + 
				(leaveMsg.empty() ? "" : " " + leaveMsg);
			channel->broadcastMessage(message);
			invoker.addReply(message);
		}
		else
		{
			strVec	args;
			args.push_back(channel->getName());
			command.replyToInvoker(442, args);
		}
	}
}

void	PART(Command& command)
{
	if (needMoreParams(command, 1))
		return;
	std::string	channelList = command.getParameters()[0];
	std::string	leaveMsg("");
	if (command.getParameters().size() > 1)
		leaveMsg = ":" + command.getParameters()[1];
	while (channelList.size())
	{
		Channel* channel = getNextChannel(channelList, command, false);
		_partUser(command, channel, leaveMsg);
	}
}