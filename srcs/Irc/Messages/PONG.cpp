/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:56:10 by esommier          #+#    #+#             */
/*   Updated: 2022/05/17 13:11:13 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	PONG(Command &command)
{
	int	response = 0;
	std::vector<std::string> args;

	Logger(Output::DEBUG) << "REPLY TO PING MESSAGE";
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

	
}
