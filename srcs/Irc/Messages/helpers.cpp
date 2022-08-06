/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:07 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/27 00:09:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcMessages.hpp"
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
		channelName = getNameFromList(channelList);
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
	return channel;
}

bool	validChannelName(std::string name)
{
	return (name[0] == '#'
		 &&	name.size() < INSPIRCD_MAX_LEN
		 && name.find(' ') == name.npos
		 && name.find(',') == name.npos
		 && name.find(7) == name.npos);
}

bool	isUserOnChannel(User* user, Channel* channel)
{
	return (channel->isMember(user));
}

bool	isUserOnChannelErr(Command &command, User* user, Channel* channel)
{
	if (channel->isMember(user))
		return true;
	strVec	args;
	args.push_back(channel->getName());
	command.replyToInvoker(442, args);
	return false;
}

void	listChannelMembers(Command &command, Channel *channel)
{
	userVec		members = channel->getMembers();
	strVec		args;
	//:<server name> 353 <nickname> = <channel name> :[nickname [...]]\r\n
	std::size_t	minMessageLen = 1 + command.getServerName().length() + 5
		+ command.getInvoker().getNickname().length() + 3 + channel->getName().length() + 2;
	std::size_t	messageLen = minMessageLen;
	
	args.push_back(channel->getName());
	if (isUserOnChannel(&command.getInvoker(), channel))
	{
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
	}
	command.replyToInvoker(366, args);
}

void	reply_403(Command & command) {
	strVec	args;
	
	args.push_back(command.getParameters()[0]);
	command.replyToInvoker(403, args);
}

bool	isUserChanop(Channel *channel, User *user) {
	return channel->getUserMode(user).find('o') != std::string::npos;
}