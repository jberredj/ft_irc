/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:34:06 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/26 22:42:55 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "helpers.hpp"
#include "User.hpp"
#include "Command.hpp"
#include <sstream>
#include <string>
#include <map>

void    LIST(Command& command)
{
	std::map<std::string, Channel*>::iterator	channelIt;
	User&										invoker = command.getInvoker();
	std::map<std::string, Channel*>*			channels = command.getChannels();

	command.replyToInvoker(321);
	for (channelIt = channels->begin() ; channelIt != channels->end(); channelIt++)
	{
		strVec				args;
		std::stringstream	nbrMember;
		Channel*			channel = (*channelIt).second;
		std::string			channelName = "*";

		if (isUserOnChannel(&invoker, channel) || true/* (!channel->hasMode(ChannelMode::CMODE_P) 
		&& !channel->hasMode(ChannelMode::CMODE_S))*/) // TODO IMPLEMENT MODE CHECKING
			channelName = channel->getName();
		else if (false /*channel->hasMode(ChannelMode::CMODE_S))*/) // If channel is Secret and user is not a member of it, we should not display the channel
			continue;
		args.push_back(channelName);
		nbrMember << channel->getNbrMember();
		args.push_back(nbrMember.str());
		if (channelName != "*" && channel->hasTopic())
			args.push_back(channel->getTopic());
		command.replyToInvoker(322, args);
	}
	command.replyToInvoker(323);
}