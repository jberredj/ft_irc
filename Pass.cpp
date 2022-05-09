/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:59:32 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/09 23:20:50 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "User.cpp"

void    PASS(Command &command)
{
    if (!command.getParameters().size())
    {
        std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
        return ;
    }
    if (command.getUser().getUstatus() != PASSWORD)
    {
        std::cout << "ERR_ALREADYREGISTRED" << std::endl;
        return ;
    }
    if (command.getParameters()[0] == "password")
        command.getUser().setUstatus(REGISTER);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
}