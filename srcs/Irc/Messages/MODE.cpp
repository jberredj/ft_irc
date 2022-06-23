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
#include "helpers.hpp"
#include "IrcMessages.hpp"

static void mode_channel(Command &command) {
	std::cout << "Mode channel spotted" << std::endl;
	std::cout << command.getParameters()[0] << std::endl;
	std::cout << command.getParameters()[1] << std::endl;
	std::string flags = "opsitnbv";
	
	
	return;
}

static bool _user_is_operator(User &user) {
	return (user.getMode().find("o") != std::string::npos);
}

static bool _command_refers_to_user(Command &command) {
	return (command.getParameters().front() == command.getInvoker().getNickname());
}

static void mode_user(Command &command) { // TODO : Seems to have some bug (Try to remove one or several flag at once)
	std::vector<std::string> args;
	User &user = command.getInvoker();
	bool minus_flag = false;
	std::string requested_mode;
    std::string new_mode;
	std::string u_flags = "-+iwso";

	if (!_user_is_operator(user) || !_command_refers_to_user(command))
	{
		return command.replyToInvoker(502, args);
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
			return command.replyToInvoker(501, args);
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
	args.push_back(new_mode);
	return command.replyToInvoker(221, args);	
}

void	MODE(Command &command)
{
	std::vector<std::string> args;
	if (command.getParameters().size() < 2) // TODO : Not true, you can call /mode nick to get the current modes without giving another parameter
	{
		args.push_back(command.getCommand());
		return command.replyToInvoker(461, args);
	}

	if (validChannelName(command.getParameters().front())) 
		mode_channel(command);
	else 
		mode_user(command);
}