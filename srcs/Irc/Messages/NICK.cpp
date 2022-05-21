/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:27:14 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/21 14:34:45 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"
#include <cctype> 

int isspchar(char c)
{
	if ((c >= '[' && c <= '`') || (c >= '{' && c <= '}'))
		return 1;
	return 0;
} 

void    NICK(Command &command)
{ 
	int response = 0;
	std::vector<std::string> args;
	std::string nick;
	
	Logger(Output::DEBUG) << "SPECIFY NICK";
	if(command.getParameters().size() == 0)
	{
		response = 431;
        return command.reply(response, args);
	}
	if(command.getParameters().size() == 1 || command.getParameters().size() == 2)
		nick = command.getParameters()[0];
	if (User *toNick = command.getUser(nick))
	{
		response = 433;
		args.push_back(nick);
		return command.reply(response, args);
	}
	if (nick.size() > 9)
	{
		response = 432;
		args.push_back(nick.substr(0,9));
		return command.reply(response, args);
	}
	if (isdigit(nick[0]) || nick[0] == '-')
	{
		response = 432;
		args.push_back(nick);
		return command.reply(response, args);
	}
	for (size_t i = 1; i < nick.size(); i++)
	{
		if (!isdigit(nick[i]) && !isalpha(nick[i]) && !isspchar(nick[i]))
		{
			response = 432;
			args.push_back(nick);
			return command.reply(response, args);
		}
	}
	command.getUser().rename(nick);
	command.getUser()._nickUsed = true;
	command.getUser().tryAuthentificate(command);
}