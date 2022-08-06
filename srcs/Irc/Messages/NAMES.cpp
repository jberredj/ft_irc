/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 23:59:45 by jberredj          #+#    #+#             */
/*   Updated: 2022/08/06 15:57:52 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"
#include <vector>

std::vector<Channel *>  _getChannelVec(Command& command, std::string channelList)
{
	Channel* channel;
	std::vector<Channel *>  channelVec;
	while (!channelList.empty() && (channel = getNextChannel(channelList, command, false)))
		if (channel)
			channelVec.push_back(channel);
	return channelVec;
}

void    NAMES(Command& command)
{
	if (command.getParameters().size())
	{
		std::vector<Channel *>  channels = _getChannelVec(command, command.getParameters()[0]);
		channelIterator         channelIt;
		for (channelIt = channels.begin(); channelIt != channels.end(); channelIt++)
			listChannelMembers(command, (*channelIt));
	}
	else
	{
		strVec  args;
		args.push_back("*");
		command.replyToInvoker(366, args);
	}
}