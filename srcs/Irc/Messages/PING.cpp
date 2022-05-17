/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:55:54 by esommier          #+#    #+#             */
/*   Updated: 2022/05/17 14:02:32 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	PING(Command &command)
{
	int	response = 0;
	std::vector<std::string> args;

	Logger(Output::DEBUG) << "TEST PRESENCE ACTIVE CLIENT";
	// if (command.***)  // no such server
	// {
	// 	response = 402;
	// 	args.push_back(command.getCommand());
	// 	return command.reply(response, args);
	// }

	if (command.getParameters().size() == 0)
	{
		response = 409;
		args.push_back(command.getCommand());
		return command.reply(response, args);
	}
	Logger(Output::DEBUG) << "PONG";
	


}