/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:35:49 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/08 23:06:49 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void	PRIVMSG(Command& command)
{
	int	response = 0;
	std::vector<std::string> args;
	User *user = ft::null_ptr;
	// const std::vector<std::string>& recepients = command.getParameters();
 
	Logger(Output::DEBUG) << "ENTERED IN PRIVMSG";
	if (command.getParameters().size() < 1)
	{
		response = 411;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}
	if (command.getTrailer().size() == 0)
	{
		response = 412;
		args.push_back(command.getCommand());
		return command.replyToInvoker(response, args);
	}

	std::string recepients = command.getParameters()[0];
	std::vector<std::string>::iterator it;
	
	std::string receiver;

	while (recepients.length())
	{
		std::size_t	comma = recepients.find(',');
		if (comma == recepients.npos)
			comma = recepients.length();
		receiver = recepients.substr(0, comma);
		// check user ou channel 
		//* User = getChannel(std::string = channel name = receiver) or getUser(nick = receiver) check if NULL
		args.push_back(command.getParameters()[1]);
		command.invokerSendTo(user, -2, args);
		args.clear();		
		if (comma != recepients.length())
			comma++;
		recepients.erase(0, comma);
	}
}