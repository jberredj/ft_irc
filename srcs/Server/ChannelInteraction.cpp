/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelInteraction.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 01:09:10 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 01:26:21 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include "typedefs.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void	Server::addChannel(Channel *channel)
{
	if (!channel)
		return ;
	std::map<std::string, Channel*>::iterator it;
	for (it = _channels.begin(); it != _channels.end(); it++)
		if ((*it).second == channel)
			return;
	_channels.insert(std::make_pair(channel->getName(), channel));
}

Channel*	Server::getChannel(std::string name)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = _channels.begin(); it != _channels.end(); it++)
		if ((*it).first == name)
			return (*it).second;
	return ft::null_ptr;
}

std::map<std::string, Channel*>*	Server::getChannels(void) {return &_channels;}

void	Server::_pruneChannel()
{
	std::map<std::string, Channel*>::iterator it;
	std::vector<std::map<std::string, Channel*>::iterator> channelToRemove;
	for (it = _channels.begin(); it != _channels.end(); it++)
		if (!(*it).second->isAlive())
			channelToRemove.push_back(it);
	std::vector<std::map<std::string, Channel*>::iterator>::iterator ohGodThatSyntax;
	for (ohGodThatSyntax = channelToRemove.begin(); ohGodThatSyntax != channelToRemove.end(); ohGodThatSyntax++)
		_channels.erase((*ohGodThatSyntax));
}