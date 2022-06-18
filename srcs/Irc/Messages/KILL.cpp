/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:35:26 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/16 22:12:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void    KILL(Command& command)
{
	int response = 0;
	std::vector<std::string> args;
    User *user = ft::null_ptr;
 
	Logger(Output::DEBUG) << "ENTERED IN KILL";
    if (command.getParameters().size() < 2)
	{
		response = 461;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}
    user = &command.getInvoker();
    if (user == ft::null_ptr)
	{
		response = 401;
		args.push_back(command.getParameters()[1]);
		return command.replyToInvoker(response, args);
	}
    if (user->getMode().find("o") == std::string::npos)
    {
        response = 481;
        return command.replyToInvoker(response, args);
    }
	args.push_back(command.getParameters()[0]);
	args.push_back(command.getTrailer());
	command.replyToInvoker(-4, args);
    command.getInvoker().setStatus(User::OFFLINE);    
}

