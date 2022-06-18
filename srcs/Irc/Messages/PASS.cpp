/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:59:32 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/08 16:16:36 by jberredj         ###   ########.fr       */
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

	if (command.getParameters().size() < 1)
	{
		response = 461;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}
	if (command.getInvoker().getStatus() != User::PASSWORD)
	{
		return command.replyToInvoker(462);
	}
	command.getInvoker().setPassword(command.getParameters()[0]);
	command.getInvoker().tryAuthentificate(command);
}