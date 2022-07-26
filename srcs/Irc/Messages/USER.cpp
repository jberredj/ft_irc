/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:36:58 by esommier          #+#    #+#             */
/*   Updated: 2022/06/26 16:23:53 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	USER(Command &command)
{
	std::vector<std::string> args;

	if (command.getParameters().size() < 4)
	{
		args.push_back(command.getCommand());
		return command.replyToInvoker(461, args);
	}
	if (command.getInvoker().getStatus() != User::PASSWORD)
		return command.replyToInvoker(462, args);
	command.getInvoker().setUsername(command.getParameters()[0]);
	command.getInvoker().setTruename(command.getTrailer());
	command.getInvoker().tryAuthentificate(command);
}
