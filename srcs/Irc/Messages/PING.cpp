/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:55:54 by esommier          #+#    #+#             */
/*   Updated: 2022/06/08 15:54:01 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	PING(Command &command)
{
	int	response = 0;
	std::vector<std::string> args;

	if (command.getParameters().size() == 0)
	{
		response = 409;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}
	std::string	serverName = command.getServerName();
	std::string reply(":");
	if (command.getParameters().size() > 1)
		args.push_back(command.getParameters()[1]);
	else
		args.push_back(serverName);
	args.push_back(command.getParameters()[0]);
	reply += serverName + " PONG " + RPL_PONG(args);
	command.getInvoker().addReply(reply);
}