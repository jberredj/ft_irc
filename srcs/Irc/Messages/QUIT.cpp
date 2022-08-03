/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:38:44 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/22 23:30:33 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	QUIT(Command& command)
{
	std::vector<std::string> args;
 
	Logger(Output::DEBUG) << "ENTERED IN QUIT";
	
	args.push_back(command.getInvoker().getUsername());
	args.push_back(command.getInvoker().getHostname());
	
	if (command.getTrailer().size() != 0)
		args.push_back(command.getTrailer());
	else
		args.push_back("leaving");
	command.replyToInvoker(-3, args);
	command.replyAllReachable(":" + command.getInvoker().getPrefix() + " QUIT :" + *(args.end() - 1));
	command.getInvoker().setStatus(User::OFFLINE);
}