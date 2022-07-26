/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:58:31 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/24 19:30:16 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void    OPER(Command& command)
{
    User &user = command.getInvoker();
	std::vector<std::string> args;
    std::string operPwd = "operPwd";

    Logger(Output::DEBUG) << "ENTERED IN OPER";
    if (command.getParameters().size() < 2)
	{
		args.push_back(command.getCommand());
		return command.replyToInvoker(461, args);
	}
    if (command.getParameters()[1] != operPwd)
		return command.replyToInvoker(464, args);
    command.replyToInvoker(381, args);
    user.addMode(UserMode::UMODE_O);
	args.push_back(user.getModesList());
    return command.replyToInvoker(221, args);      
}
