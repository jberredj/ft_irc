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

static void _mode_channel(Command &command) {
	std::cout << "Mode channel spotted" << std::endl;
	std::cout << command.getParameters()[0] << std::endl;
	std::cout << command.getParameters()[1] << std::endl;
	std::string flags = "opsitnbv";
	
	
	return;
}

static void _mode_user(Command &command) {
	std::vector<std::string> args;
	User &user = command.getInvoker();
	std::string uflags = "iwso";
	std::string flagChanges = "";

	if (!command.targetsInvoker())
		return command.replyToInvoker(502, args);
	std::string requestedMode = command.getParameters()[1];
	bool addFlag = true;

	for (size_t i = 0; i < requestedMode.size(); i++)
	{
		if (requestedMode[i] == '-')
			addFlag = false;
		else if (requestedMode[i] == '+')
			addFlag = true;
		else if (uflags.find(requestedMode[i]) == std::string::npos)
			command.replyToInvoker(501, args);
		else if (addFlag && requestedMode[i] == 'o')
			continue;
		else if (addFlag && !user.hasMode(UserMode::modesMap[requestedMode[i]])) {
			user.addMode(UserMode::modesMap[requestedMode[i]]);
			flagChanges += "+";
			flagChanges += requestedMode[i];
		}
		else if (!addFlag && user.hasMode(UserMode::modesMap[requestedMode[i]])) {
			user.removeMode(UserMode::modesMap[requestedMode[i]]);
			flagChanges += "-";
			flagChanges += requestedMode[i];
		}
	}
	if (!flagChanges.empty()) {
		args.push_back(user.getNickname());
		args.push_back(flagChanges);
		command.invokerSendTo(&user, -5, args);
	}
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
		_mode_channel(command);
	else 
		_mode_user(command);
}
