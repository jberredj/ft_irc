/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:58:31 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/12 20:23:48 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void    OPER(Command& command)
{
    User &user = command.getUser();
	int response = 0;
	std::vector<std::string> args;
    std::string operPwd = "operPwd";

    if (command.getParameters().size() < 2)
	{
		response = 461;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}
    if (command.getParameters()[1] != operPwd)
    {
        response = 464;
		return command.replyToInvoker(response, args);
    }
    
    std::string modeO = user.getMode();
    modeO = modeO + "o";
    user.setMode(modeO);
    response = 381;
    return command.replyToInvoker(response, args);      
}
