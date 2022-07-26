/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:13:22 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/19 14:44:45 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Channel.hpp"
#include "User.hpp"
#include "helpers.hpp"
#include "typedefs.hpp"

void TOPIC(Command &command) {
	if (needMoreParams(command, 1))
		return ;
	User&		invoker = command.getInvoker();
	Channel*	channel = command.getChannel(command.getParameters()[0]);
	if (!channel)
		return ;
	if (!isUserOnChannelErr(command, &invoker, channel))
		return;
	if (/*!channel->hasMode(ChannelMode::CMODE_T)*/ false || channel->isOperator(&invoker))
	{
		channel->setTopic(command.getTrailer());
		channel->broadcastMessage(":" + invoker.getPrefix() + " TOPIC " + channel->getName() + " :"
			+ command.getTrailer());
	}
	else
	{
		strVec	args;
		args.push_back(channel->getName());
		command.replyToInvoker(482, args);
	}
}