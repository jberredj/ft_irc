/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:36:58 by esommier          #+#    #+#             */
/*   Updated: 2022/06/12 18:31:55 by ddiakova         ###   ########.fr       */
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

	if (command.getParameters().size() < 4)
	{
		response = 461;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}
	if (command.getUser().getStatus() != User::PASSWORD)
	{
		response = 462;
		return command.replyToInvoker(response, args);
	}
	command.getUser().setUsername(command.getParameters()[0]);
	// command.getUser().setHostname(command.getParameters()[1]);
	command.getUser().setServername(command.getParameters()[2]);
	command.getUser().setTruename(command.getTrailer());
	command.getUser().setUserUsed(true);
	command.getUser().tryAuthentificate(command);	
}
