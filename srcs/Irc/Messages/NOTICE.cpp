/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 12:12:11 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/26 18:21:21 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"

static void	noticeUser(Command& command, std::string str_receiver)
{
	std::vector<std::string> args;
	User	*user = ft::null_ptr;

	user = command.getUser(str_receiver);
	if (user == ft::null_ptr)
		return ;
	args.push_back(str_receiver);
	args.push_back(command.getTrailer());
	command.invokerSendTo(user, -8, args);
	args.clear();
}

static void	noticeChannel(Command& command, std::string str_receiver)
{
	std::vector<std::string> args;
	Channel	*channel = ft::null_ptr;

	if (!validChannelName(str_receiver))
		return ;
	channel = command.getChannel(str_receiver);
	args.push_back(str_receiver);
	channel->broadcastMessage(":" + command.getInvoker().getPrefix() +" NOTICE " + str_receiver + " :" 
		+ command.getTrailer(), &command.getInvoker());
}

void	NOTICE(Command& command)
{
	std::vector<std::string> args;
	Logger(Output::DEBUG) << "ENTERED IN NOTICE";
	
	if (command.getParameters().size() == 0)
        return ;
	if (command.getTrailer().size() == 0)
		return ;

	std::string receiver = command.getParameters()[0];

	if (receiver[0] == '#')
		noticeChannel(command, receiver);
	else
		noticeUser(command, receiver);	
	receiver.erase();
}