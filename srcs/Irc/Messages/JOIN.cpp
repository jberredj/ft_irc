/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:21:35 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 22:42:06 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"
#include "typedefs.hpp"

Channel*	_getNextChannel(std::string& channelList, Command& command)
{
	std::string	channelName = getNameFromList(channelList);
	while (!validChannelName(channelName))
	{
		strVec	args;
		args.push_back(channelName);
		command.replyToInvoker(403, args);
		std::string	channelName = getNameFromList(channelList);
	}
	if (channelName.empty())
		return ft::null_ptr;
	
	Channel*	channel = command.getChannel(channelName);
	if (!channel)
	{
		Logger(Output::DEBUG) << "Create a new channel: " << channelName;
		channel = new Channel(channelName);
		command.addChannel(channel);
	}
	return channel;
}

void	JOIN(Command &command)
{
	if (needMoreParams(command, 1))
		return;
	std::string	channelList = command.getParameters()[0];
	Channel*	channel = ft::null_ptr;
	while ((channel = _getNextChannel(channelList, command)))
	{
		// Check if User can JOin
		if (channel->addUser(&command.getUser()))
			channel->broadcastMessage(":" + command.getUser().getPrefix() + " JOIN :" + channel->getName());
	}
	
}