/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:56:10 by esommier          #+#    #+#             */
/*   Updated: 2022/07/27 02:08:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	PONG(Command &command)
{
	User &invoker = command.getInvoker();
	bool			success = false;
	if (command.getParameters().empty())
		return ;
	if (invoker.getExpectedPONG().empty())
		return ;
	if (invoker.getExpectedPONG() == command.getTrailer())
		success = true;
	if (success) {
		invoker.updateSeenTime();
		invoker.setExpectedPONG("");
		if (invoker.getStatus() <= User::REGISTER) {
			strVec	args;
			args.push_back(invoker.getPrefix());
			invoker.setStatus(User::ONLINE);
			invoker.setTimeout(120);
			command.replyToInvoker(1, args);
		}
	}
	else if (invoker.getStatus() <= User::REGISTER) {
		strVec args;
		invoker.setStatus(User::OFFLINE);
		args.push_back(invoker.getUsername());
    	args.push_back(invoker.getHostname());
		command.replyToInvoker(-6, args);
	}
}

