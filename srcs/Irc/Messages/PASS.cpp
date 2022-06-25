/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:59:32 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/24 19:30:33 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	PASS(Command& command)
{
	std::vector<std::string> args;

	if (command.getParameters().size() < 1)
	{
		args.push_back(command.getCommand());
		return command.replyToInvoker(461, args);
	}
	if (command.getInvoker().getStatus() != User::PASSWORD)
	{
		return command.replyToInvoker(462);
	}
	command.getInvoker().setPassword(command.getParameters()[0]);
	command.getInvoker().tryAuthentificate(command);
}