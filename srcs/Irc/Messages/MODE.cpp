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
#include "UserModeCommand.hpp"

static void _mode_channel(Command &command) {
	std::cout << "Mode channel spotted" << std::endl;
	(void) command;
	// std::cout << command.getParameters()[0] << std::endl;
	// std::cout << command.getParameters()[1] << std::endl;
	// std::string flags = "opsitnbv";
	
	
	return;
}

static void _mode_user(Command &command) {
	UserModeCommand foo = UserModeCommand(command);
	foo.updateModes();
}

void	MODE(Command &command)
{
	std::vector<std::string> args;
	if (command.getParameters().size() < 1)
	{
		args.push_back(command.getCommand());
		return command.replyToInvoker(461, args);
	}

	if (validChannelName(command.getParameters().front())) 
		_mode_channel(command);
	else 
		_mode_user(command);
}
