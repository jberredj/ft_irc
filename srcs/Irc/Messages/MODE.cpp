/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:30:20 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/08 15:12:44 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	MODE(Command &command)
{
    User &user = command.getInvoker();
	int response = 0;
	std::vector<std::string> args;
	bool minus_flag = false;
	std::string requested_mode;
    std::string new_mode;
	std::string u_flags = "-+iwso";

	if (command.getParameters().size() < 2)
	{
		response = 461;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}
	if (command.getParameters()[0] != user.getNickname() && user.getMode().find("o") == std::string::npos)
	{
		response = 502;
		return command.replyToInvoker(response, args);
	}
	requested_mode = command.getParameters()[1];
    new_mode = user.getMode();
	for (size_t i = 0; i < requested_mode.size(); i++)
	{
		if (requested_mode[i] == '-')
			minus_flag = true;
		else if (requested_mode[i] == '+')
			minus_flag = false;
		else if (u_flags.find(requested_mode[i]) == std::string::npos)
		{
			response = 501;
			return command.replyToInvoker(response, args);
		}
		else if (requested_mode[i] == 'o' && !minus_flag && new_mode.find("o") == std::string::npos)
			continue;
		else
		{
			size_t	modeSet = new_mode.find(requested_mode[i]);
			if (minus_flag && modeSet != std::string::npos)
				new_mode.erase(modeSet);
			else if(!minus_flag && modeSet == std::string::npos)
				new_mode = new_mode + requested_mode[i];
		}
	}
	user.setMode(new_mode);
	response = 221;
	args.push_back(new_mode);
	return command.replyToInvoker(response, args);	
}