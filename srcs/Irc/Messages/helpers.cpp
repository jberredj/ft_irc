/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:07 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/23 09:58:03 by jberredj         ###   ########.fr       */
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
	if (!channel && createIfNotExist)
	{
		Logger(Output::DEBUG) << "Create a new channel: " << channelName;
		channel = new Channel(channelName);
		command.addChannel(channel);
	}
	else if (!channel)
	{
		strVec	args;
		args.push_back(channelName);
		command.replyToInvoker(403, args);
	}
	return channel;
}

bool		validChannelName(std::string name)
{
	if (name[0] != '#' && name.size() > INSPIRCD_MAX_LEN)
		return false;
	if (name.find(' ') != name.npos || name.find(0x7) != name.npos)
		return false;
	return true;
}