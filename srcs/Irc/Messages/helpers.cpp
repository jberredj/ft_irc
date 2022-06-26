/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:07 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/24 17:09:13 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "Command.hpp"
#include "typedefs.hpp"
#include "helpers.hpp"

bool	needMoreParams(Command &command, size_t minRequired)
{
	std::vector<std::string>	args;
	if (command.getParameters().size() < minRequired)
	{
		args.push_back(command.getCommand());
		command.replyToInvoker(461, args);
		return true;
	}
	return false;
}

std::string	getNameFromList(std::string& nameList)
{
	size_t		commaLoc = nameList.find(',');
	if (commaLoc == nameList.npos)
		commaLoc = nameList.length();
	std::string	channelName = nameList.substr(0, commaLoc);
	nameList.erase(0, commaLoc);
	return channelName;
}

Channel*	getNextChannel(std::string& channelList, Command& command, bool createIfNotExist)
{
	std::string	channelName = getNameFromList(channelList);
	while (!channelName.empty() && !validChannelName(channelName))
	{
		strVec	args;
		args.push_back(channelName);
		command.replyToInvoker(403, args);
		std::string	channelName = getNameFromList(channelList);
	}
	if (channelName.empty())
		return ft::null_ptr;
	Channel*	channel = command.getChannel(channelName, false);

	if (!channel && createIfNotExist)
	{
		Logger(Output::DEBUG) << "Create a new channel: " << channelName;
		channel = new Channel(channelName);
		command.addChannel(channel);
	}
	return channel;
}

bool		validChannelName(std::string name)
{
	return (name[0] == '#'
		 &&	name.size() < INSPIRCD_MAX_LEN
		 && name.find(' ') == name.npos
		 && name.find(',') == name.npos
		 && name.find(7) == name.npos);
}

bool	isUserOnChannel(Command &command, User* user, Channel* channel)
{
	if (channel->isMember(user))
		return true;
	strVec	args;
	args.push_back(channel->getName());
	command.replyToInvoker(442, args);
	return false;
}
