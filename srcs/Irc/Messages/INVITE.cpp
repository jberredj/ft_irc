/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:03:18 by ddiakova          #+#    #+#             */
/*   Updated: 2022/07/26 22:35:38 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "helpers.hpp"
#include "User.hpp"
#include "Command.hpp"

void    INVITE(Command& command)
{
	std::vector<std::string> args;
	User	*user = ft::null_ptr;
	Channel	*channel = ft::null_ptr;
	
	if (needMoreParams(command, 2))
		return;
	std::string nick = command.getParameters()[0];
	std::string channel_str = command.getParameters()[1];
	if (!(channel = command.getChannel(channel_str)))
		return reply_403(command);
	if (!isUserOnChannel(&command.getInvoker(), channel))
		return ; // TODO - return something ?
	user = command.getUser(nick);
	if (!user)
	{
		args.push_back(nick);
		return command.replyToInvoker(401, args);
	}
	if (isUserOnChannel(user, channel))
	{
		args.push_back(user->getUsername());
		args.push_back(channel->getName());
		command.replyToInvoker(443, args);
	}
	if (!channel->isOperator(&command.getInvoker()))
	{
		args.push_back(channel->getName());
		command.replyToInvoker(482, args);
	}
	channel->inviteUser(user);
	args.push_back(user->getNickname());
	args.push_back(channel->getName());
	command.invokerSendTo(user, 341, args);
}
