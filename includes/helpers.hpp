/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:48 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/27 00:05:00 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_HPP
# define HELPERS_HPP
# include "Command.hpp"
# include "Channel.hpp"

bool		needMoreParams(Command &command, size_t minRequired);
std::string	getNameFromList(std::string& nameList);
Channel*	getNextChannel(std::string& channelList, Command& command, bool createIfNotExist = true);
bool		validChannelName(std::string name);
bool		isUserOnChannel(User* user, Channel* channel);
bool		isUserOnChannelErr(Command &command, User* user, Channel* channel);
void		listChannelMembers(Command &command, Channel *channel);
void	    reply_403(Command & command);
bool	    isUserChanop(Channel *channel, User *user);

#endif
