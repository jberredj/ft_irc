/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:35:49 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/29 00:11:12 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"

static void	msgUser(Command& command, std::string str_receiver)
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

static void	msgChannel(Command& command, std::string str_receiver)
{
	std::vector<std::string> args;
	Channel *channel = ft::null_ptr;

	channel = command.getChannel(str_receiver);
	if (!channel)
		return ; // TODO - return 403
	//check n
	// check if (user in channel)
	// 		if not error and return
	
	//check modere ou pas - m
	// check if (o || v)
	//		if not error and return
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
		if (validChannelName(receiver))
			msgChannel(command, receiver);
		else
			msgUser(command,receiver);
		if (comma != recepients.length())
			comma++;
		recepients.erase(0, comma);
	}
}