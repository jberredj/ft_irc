/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:35:26 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/26 17:28:46 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void    KILL(Command& command)
{
	std::vector<std::string> args;
    User *user = ft::null_ptr;
 
	Logger(Output::DEBUG) << "ENTERED IN KILL";
    if (command.getParameters().size() < 2)
	{
		args.push_back(command.getCommand());
		return command.replyToInvoker(461, args);
	}
    user = &command.getInvoker();
    if (user == ft::null_ptr)
	{
		args.push_back(command.getParameters()[1]);
		return command.replyToInvoker(401, args);
	}
    if (!user->isOperator())
	{
        return command.replyToInvoker(481, args);
	}
	args.push_back(command.getParameters()[0]);
	args.push_back(command.getTrailer());
	command.replyToInvoker(-4, args);
    command.getInvoker().setStatus(User::OFFLINE);    
}

