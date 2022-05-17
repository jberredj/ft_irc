/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:59:32 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/17 13:46:06 by esommier         ###   ########.fr       */
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
		return command.reply(response, args);
	}
	if (command.getUser().getStatus() != User::PASSWORD)
	{
		response = 462;
		args.push_back(command.getCommand());
		return command.reply(response, args);
	}
	command.getUser().setPassword(command.getParameters()[0]);
	Logger(Output::DEBUG) << "New password " << command.getUser().getPassword();
}