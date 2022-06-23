/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:21:35 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/23 08:46:14 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "IrcMessages.hpp"
#include "helpers.hpp"
#include "typedefs.hpp"

void	JOIN(Command &command)
{
	if (needMoreParams(command, 1))
		return;
	std::string	channelList = command.getParameters()[0];
	Channel*	channel = ft::null_ptr;
	while ((channel = getNextChannel(channelList, command)))
	{
		// TODO: ADD Check if User can join
		if (channel->addUser(&command.getInvoker()))
			channel->broadcastMessage(":" + command.getInvoker().getPrefix() + " JOIN :" + channel->getName());
	}
}