/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:35:49 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/08 15:12:44 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	PASS(Command& command)
{
	int	response = 0;
	std::vector<std::string> args;

	Logger(Output::DEBUG) << "ENTERED IN PASS";
	if (command.getParameters().size() < 1)
	{
		response = 461;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}
	if (command.getUser().getStatus() != User::PASSWORD)
	{
		return command.replyToInvoker(462);
	}
	command.getUser().setPassword(command.getParameters()[0]);
	Logger(Output::DEBUG) << "New password " << command.getUser().getPassword();
	command.getUser().setPassUsed(true);
	command.getUser().tryAuthentificate(command);
}