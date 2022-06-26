/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:35:49 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/26 16:25:15 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"

void	msgUser(Command& command, std::string str_receiver)
{
	std::vector<std::string> args;
	User *user = ft::null_ptr;
	
	user = command.getUser(str_receiver);
	if (user == ft::null_ptr)
	{
		args.push_back(str_receiver);
		return command.replyToInvoker(401, args);
	}
	if (user->isAway())
	{
		args.push_back(str_receiver);
		args.push_back(user->getAwaymsg());
		command.replyToInvoker(301, args);
		args.clear();
	}
	args.push_back(str_receiver);
	args.push_back(command.getTrailer());
	command.invokerSendTo(user, -2, args);
	args.clear();		
}

void	msgChannel(Command& command, std::string str_receiver)
{
	std::vector<std::string> args;
	Channel *channel = ft::null_ptr;

	if (!validChannelName(str_receiver))
	{
		args.push_back(str_receiver);
		return command.replyToInvoker(401, args);
	}
	channel = command.getChannel(str_receiver);
	channel->broadcastMessage(":" + command.getInvoker().getPrefix() +" PRIVMSG " + str_receiver + " :" 
		+ command.getTrailer(), &command.getInvoker());
}


void	PRIVMSG(Command& command)
{
	std::vector<std::string> args;
 
	Logger(Output::DEBUG) << "ENTERED IN PRIVMSG";
	if (command.getParameters().size() < 1)
	{
		args.push_back(command.getCommand());
		return command.replyToInvoker(411, args);
	}
	if (command.getTrailer().size() == 0)
	{
		args.push_back(command.getCommand());
		return command.replyToInvoker(412, args);
	}

	std::string recepients = command.getParameters()[0];
	std::string receiver;

	while (recepients.length())
	{
		std::size_t	comma = recepients.find(',');
		if (comma == recepients.npos)
			comma = recepients.length();
		receiver = recepients.substr(0, comma);
		if (receiver[0] == '#')
			msgChannel(command, receiver);
		else
			msgUser(command,receiver);
		if (comma != recepients.length())
			comma++;
		recepients.erase(0, comma);
	}
}