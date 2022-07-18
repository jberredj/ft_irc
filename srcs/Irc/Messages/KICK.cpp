/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:16:53 by ddiakova          #+#    #+#             */
/*   Updated: 2022/07/18 22:51:55 by ddiakova         ###   ########.fr       */
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
        return ;
    if (!isUserOnChannel(command, &command.getInvoker(), channel))
        return ;
    if (!(user = command.getUser(nick)))
        return ;
    if (!channel->isOperator(&command.getInvoker()))
    {
        args.push_back(channel->getName());
        command.replyToInvoker(482, args);
        return ;
    }
    std::string	message = ":" + command.getInvoker().getPrefix() + " KICK " + curChannel + " " + user->getNickname() + (comment.empty() ? "" : " " + comment);
	channel->broadcastMessage(message);
    channel->removeUser(user);
}