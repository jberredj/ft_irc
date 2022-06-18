/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:27:14 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/11 18:05:57 by ddiakova         ###   ########.fr       */
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
	
	if(command.getParameters().size() == 0)
	{
		response = 431;
        return command.replyToInvoker(response, args);
	}
	if(command.getParameters().size() == 1 || command.getParameters().size() == 2)
		nick = command.getParameters()[0];
	if (command.getUser(nick))
	{
		response = 433;
		args.push_back(nick);
		return command.replyToInvoker(response, args);
	}
	if (nick.size() > 9)
	{
		response = 432;
		args.push_back(nick.substr(0,9));
		return command.replyToInvoker(response, args);
	}
	if (isdigit(nick[0]) || nick[0] == '*')
	{
		response = 432;
		args.push_back(nick);
		return command.replyToInvoker(response, args);
	}
	for (size_t i = 1; i < nick.size(); i++)
	{
		if (!isdigit(nick[i]) && !isalpha(nick[i]) && !isspchar(nick[i]))
		{
			response = 432;
			args.push_back(nick);
			return command.replyToInvoker(response, args);
		}
	}
	command.getInvoker().setNickname(nick);
	command.getInvoker().tryAuthentificate(command);
}