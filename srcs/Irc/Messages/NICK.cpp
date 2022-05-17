/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:27:14 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/17 20:11:58 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include <cctype> 

int isspchar(char c)
{
	if ((c >= '[' && c <= '`') || (c >= '{' && c <= '}'))
		return 1;
	return 0;
} 

void    NICK(Command &command)
{ 
	std::string nick;
	
	Logger(Output::DEBUG) << "ENTERED IN NICK";
	if(command.getParameters().size() == 0)
	{
		Logger(Output::WARN) << "(431) ERR_NONICKNAMEGIVEN" << std::endl;
        return ;
	}
	if(command.getParameters().size() == 1 || command.getParameters().size() == 2)
		nick = command.getParameters()[0];
	else
		return;
	if (nick.size() > 9)
	{
		Logger(Output::WARN) << "(432) ERR_ERRONEUSNICKNAME" << std::endl;
        return ;
		// nick = substr.nick(0, 9);
	}
	if (isdigit(nick[0]) || nick[0] == '-')
	{
		Logger(Output::WARN) << "(432) ERR_ERRONEUSNICKNAME" << std::endl;
        return ;
	}
	for (int i = 1; i < nick.size(); i++)
	{
		if (!isdigit(nick[i]) && !isalpha(nick[i]) && !isspchar(nick[i]))
		{
			Logger(Output::WARN) << "(432) ERR_ERRONEUSNICKNAME" << std::endl;
        	return ;
		}
	}
	if (nick == "-" && nick == command.getUser().getNickname())
	{
		Logger(Output::WARN) << "(436) ERR_NICKCOLLISION" << std::endl;
        return ;
	}
	if(nick == command.getUser().getNickname())
	{
		Logger(Output::WARN) << "(433) ERR_NICKNAMEINUSE" << std::endl;
		return ;
	}
	command.getUser().reName(nick);
}