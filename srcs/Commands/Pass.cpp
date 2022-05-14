/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:59:32 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/14 23:21:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"

void    PASS(Command &command)
{
    Logger(Output::DEBUG) << "ENTERED IN PASS";
    if (command.getParameters().size() < 1)
    {
        Logger(Output::WARN) << "ERR_NEEDMOREPARAMS" << std::endl;
        return ;
    }
    if (command.getUser().getStatus() != User::PASSWORD)
    {
        Logger(Output::WARN) << "ERR_ALREADYREGISTRED" << std::endl;
        return ;
    }
    command.getUser().setPassword(command.getParameters()[0]);
    Logger(Output::DEBUG) << "New password " << command.getUser().getPassword();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}