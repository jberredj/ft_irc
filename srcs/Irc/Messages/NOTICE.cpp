/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 12:12:11 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/12 15:15:02 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	NOTICE(Command& command)
{
	std::vector<std::string> args;
	User *user = ft::null_ptr;
 
	Logger(Output::DEBUG) << "ENTERED IN NOTICE";
	
	if (command.getParameters().size() == 0)
        return ;
	if (command.getTrailer().size() == 0)
		return ;

	std::string receiver = command.getParameters()[0];

	// if (receiver[0] == '#')
	// 	user = command.getChannel(receiver);
	// else
		user = command.getUser(receiver);
	if (user == ft::null_ptr)
		return ;
	args.push_back(receiver);
	args.push_back(command.getTrailer());
	command.invokerSendTo(user, -2, args);
	args.clear();		
	receiver.erase();
}