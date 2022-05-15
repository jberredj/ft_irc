/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:59:32 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/15 19:19:03 by ddiakova         ###   ########.fr       */
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
        Logger(Output::WARN) << "(461) ERR_NEEDMOREPARAMS" << std::endl;
        return ;
    }
    if (command.getUser().getStatus() != User::PASSWORD)
    {
        Logger(Output::WARN) << "(462) ERR_ALREADYREGISTRED" << std::endl;
        return ;
    }
    command.getUser().setPassword(command.getParameters()[0]);
    Logger(Output::DEBUG) << "New password " << command.getUser().getPassword();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}