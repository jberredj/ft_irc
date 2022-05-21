/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:36:58 by esommier          #+#    #+#             */
/*   Updated: 2022/05/21 12:44:00 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	USER(Command &command)
{
	int	response = 0;
	std::vector<std::string> args;

	Logger(Output::DEBUG) << "SPECIFY NEW USER ";
	if (command.getParameters().size() < 3)
	{
		response = 461;
		args.push_back(command.getCommand());
		return command.reply(response, args);
	}
	if (command.getUser().getStatus() != User::PASSWORD)
	{
		response = 462;
		return command.reply(response, args);
	}
	command.getUser().setUsername(command.getParameters()[0]);
	command.getUser().setHostname(command.getParameters()[1]);
	command.getUser().setTruename(command.getTrailer());
	Logger(Output::DEBUG) << "User: " << command.getUser().getUsername()
	<< " " << command.getUser().getHostname()
	<< " " << command.getUser().getTruename();
	command.getUser()._userUsed = true;
	
}
