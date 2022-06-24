/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:48 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/24 16:38:02 by jberredj         ###   ########.fr       */
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
bool		isUserOnChannel(Command &command, User* user, Channel* channel);
#endif