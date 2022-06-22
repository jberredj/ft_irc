/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWAY.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:44:24 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/22 10:51:44 by jberredj         ###   ########.fr       */
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
		command.getInvoker().getAwaymsg().clear();
	}
	else
	{
		command.getInvoker().setAwayMsg(command.getTrailer());
		command.replyToInvoker(306, args);
	}
}