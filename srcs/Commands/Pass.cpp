/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:59:32 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/14 16:39:52 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "User.hpp"

void    PASS(Command &command)
{
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
    if (command.getParameters()[0] == command.getUser().getPassword())
        command.getUser().setStatus(User::REGISTER);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
}