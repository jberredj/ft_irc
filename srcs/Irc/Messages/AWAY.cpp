/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWAY.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:44:24 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/19 17:48:31 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	AWAY(Command& command)
{
	std::vector<std::string> args;

	Logger(Output::DEBUG) << "ENTERED IN AWAY";
	if (command.getParameters().size() == 0)
	{
		command.replyToInvoker(305, args);
		command.getUser().getAwaymsg().clear();
	}
	else
	{
		command.getUser().setAwayMsg(command.getTrailer());
		command.replyToInvoker(306, args);
	}
}