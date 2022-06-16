/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:07 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 22:04:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "Command.hpp"

bool	needMoreParams(Command &command, size_t minRequired)
{
	std::vector<std::string>	args;
	if (command.getParameters().size() < minRequired)
	{
		args.push_back(command.getCommand());
		command.replyToInvoker(461, args);
		return true;
	}
	return false;
}

std::string	getNameFromList(std::string& nameList)
{
	size_t		commaLoc = nameList.find(',');
	if (commaLoc == nameList.npos)
		commaLoc = nameList.length();
	std::string	channelName = nameList.substr(0, commaLoc);
	nameList.erase(0, commaLoc);
	return channelName;
}