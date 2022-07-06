/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:16:53 by ddiakova          #+#    #+#             */
/*   Updated: 2022/07/06 21:36:08 by ddiakova         ###   ########.fr       */
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
    std::string username = command.getParameters()[1];
    if (command.getParameters().size() > 2)
        comment = ":" + command.getParameters()[2];
    if (!(channel = command.getChannel(curChannel)))
    {
        args.push_back(curChannel);
        command.replyToInvoker(403, args);
        return ;
    }
    if (!isUserOnChannel(command, &command.getInvoker(), channel))
        return ;
    if (!(user = command.getUserFromName(username)))
        return ;
    if (!channel->isOperator(&command.getInvoker()))
    {
        args.push_back(channel->getName());
        command.replyToInvoker(482, args);
        return ;
    }
    channel->removeUser(user);
    std::string	message = ":" + user->getPrefix() + " KICK " + curChannel + (comment.empty() ? "" : " " + comment);
	channel->broadcastMessage(message);
}


//442     ERR_NOTONCHANNEL
                //         "<channel> :You're not on that channel"

                // - Returned by the server whenever a client tries to
                //   perform a channel effecting command for which the
                //   client isn't a member.

//403     ERR_NOSUCHCHANNEL
                       // "<channel name> :No such channel"

//482     ERR_CHANOPRIVSNEEDED
                        //"<channel> :You're not channel operator"
