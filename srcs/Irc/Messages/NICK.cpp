/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:27:14 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/26 16:23:29 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"
#include <cctype> 

static	int isspchar(char c)
{
	if ((c >= '[' && c <= '`') || (c >= '{' && c <= '}'))
		return 1;
	return 0;
} 

void    NICK(Command &command)
{ 
	User &user = command.getInvoker();
	std::vector<std::string> args;
	std::string nick;
	
	if(command.getParameters().size() == 0)
        return command.replyToInvoker(431, args);
	if(command.getParameters().size() == 1 || command.getParameters().size() == 2)
		nick = command.getParameters()[0];
	if (command.getUser(nick))
	{
		args.push_back(nick);
		return command.replyToInvoker(433, args);
	}
	if (nick.size() > 30)
		return command.replyToInvoker(432, args);
	if (isdigit(nick[0]) || nick[0] == '*')
	{
		args.push_back(nick);
		return command.replyToInvoker(432, args);
	}
	for (size_t i = 1; i < nick.size(); i++)
	{
		if (!isdigit(nick[i]) && !isalpha(nick[i]) && !isspchar(nick[i]))
		{
			args.push_back(nick);
			return command.replyToInvoker(432, args);
		}
	}
	if (!user.getNickname().length()) 
		return ;
	args.push_back(nick);
	command.invokerSendTo(&user, -7, args);
	user.setNickname(nick);
}