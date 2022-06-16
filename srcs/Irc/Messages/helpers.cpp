/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:07 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 22:42:37 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "Command.hpp"
#include "typedefs.hpp"

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

bool		validChannelName(std::string name)
{
	if (name[0] != '#'
		&& name.size() > INSPIRCD_MAX_LEN)
		return false;
	if (name.find(' ') != name.npos || name.find(0x7) != name.npos)
		return false;
	return true;
}