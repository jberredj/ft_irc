/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:21:35 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 22:05:56 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"
#include "typedefs.hpp"

bool		_validChannelName(std::string name)
{
	if (name[0] != '#'
		&& name.size() > INSPIRCD_MAX_LEN)
		return false;
	if (name.find(' ') != name.npos || name.find(0x7) != name.npos)
		return false;
	return true;
}

Channel*	_getNextChannel(std::string& channelList, Command& command)
{
	std::string	channelName = getNameFromList(channelList);
	while (!_validChannelName(channelName))
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