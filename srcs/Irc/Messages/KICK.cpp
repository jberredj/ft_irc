/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:16:53 by ddiakova          #+#    #+#             */
/*   Updated: 2022/07/19 14:44:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "helpers.hpp"
#include "User.hpp"
#include "Command.hpp"

void    KICK(Command& command)
{
	std::vector<std::string> args;
	User	*user = ft::null_ptr;
	Channel	*channel = ft::null_ptr;
	std::string comment = "";
	
	if (needMoreParams(command, 2))
		return;
	std::string curChannel = command.getParameters()[0];
	std::string nick = command.getParameters()[1];
	if (command.getTrailer().size())
		comment = ":" + command.getTrailer();
	if (!(channel = command.getChannel(curChannel)))
		return reply_403(command);
	if (!isUserOnChannelErr(command, &command.getInvoker(), channel))
		return ;
	if (!(user = command.getUser(nick)))
		return ;
	if (!channel->isOperator(&command.getInvoker()))
	{
		args.push_back(channel->getName());
		args.push_back("halfop");
		args.push_back("o");
		args.push_back("op");

		command.replyToInvoker(482, args);
		return ;
	}
	std::string	message = ":" + command.getInvoker().getPrefix() + " KICK " + curChannel + " " + user->getNickname() + (comment.empty() ? "" : " " + comment);
	channel->broadcastMessage(message);
	channel->removeUser(user);
}