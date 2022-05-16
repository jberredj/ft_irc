/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessages.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:52:17 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/17 01:03:42 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGES_HPP
# define IRCMESSAGES_HPP
# include "Command.hpp"
# include <string>
# include <vector>
void	PASS(Command& command);

//Replies
std::string	RPL_WELCOME(std::vector<std::string> args);
std::string	RPL_UMODEIS(std::vector<std::string> args);
std::string	RPL_AWAY(std::vector<std::string> args);
std::string	RPL_WHOISUSER(std::vector<std::string> args);
std::string	RPL_WHOISSERVER(std::vector<std::string> args);
std::string	RPL_WHOISOPERATOR(std::vector<std::string> args);
std::string	RPL_WHOISIDLE(std::vector<std::string> args);
std::string	RPL_ENDOFWHOIS(std::vector<std::string> args);
std::string	RPL_WHOISCHANNELS(std::vector<std::string> args);
std::string	RPL_LISTSTART(std::vector<std::string> args);
std::string	RPL_LIST(std::vector<std::string> args);
std::string	RPL_LISTEND(std::vector<std::string> args);
std::string	RPL_NOTOPIC(std::vector<std::string> args);
std::string	RPL_TOPIC(std::vector<std::string> args);
std::string	RPL_INVITING(std::vector<std::string> args);
std::string	RPL_NAMREPLY(std::vector<std::string> args);
std::string	RPL_ENDOFNAMES(std::vector<std::string> args);
std::string	RPL_YOUREOPER(std::vector<std::string> args);
std::string	RPL_USERSSTART(std::vector<std::string> args);
std::string	RPL_USERS(std::vector<std::string> args);
std::string	RPL_ENDOFUSERS(std::vector<std::string> args);
std::string	RPL_NOUSERS(std::vector<std::string> args);

#endif