/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:35:49 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/22 18:54:56 by jberredj         ###   ########.fr       */
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
	int	response = 0;
	std::vector<std::string> args;
	User *user = ft::null_ptr;
	
	user = command.getUser(str_receiver);
	if (user == ft::null_ptr)
	{
		response = 401;
		args.push_back(str_receiver);
		return command.replyToInvoker(response, args);
	}
	if (user->isAway())
	{
		response = 301;
		args.push_back(str_receiver);
		args.push_back(user->getAwaymsg());
		command.replyToInvoker(response, args);
		args.clear();
	}
	args.push_back(str_receiver);
	args.push_back(command.getTrailer());
	command.invokerSendTo(user, -2, args);
	args.clear();		
}

void	msgChannel(Command& command, std::string str_receiver)
{
	int	response = 0;
	std::vector<std::string> args;
	Channel *channel = ft::null_ptr;

	if (!validChannelName(str_receiver))
	{
		response = 401;
		args.push_back(str_receiver);
		return command.replyToInvoker(response, args);
	}
	channel = command.getChannel(str_receiver);
	channel->broadcastMessage(":" + command.getInvoker().getPrefix() +" PRIVMSG " + str_receiver + " :" 
		+ command.getTrailer(), &command.getInvoker());
}


void	PRIVMSG(Command& command)
{
	int	response = 0;
	std::vector<std::string> args;
 
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