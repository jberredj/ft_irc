/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessages.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:52:17 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 22:13:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGES_HPP
# define IRCMESSAGES_HPP
# include "Command.hpp"
# include <string>
# include <vector>
# ifndef IRC_MESSAGE_LEN
#  define IRC_MESSAGE_LEN 512
# endif
void	PASS(Command &command);
void	USER(Command &command);
void    NICK(Command &command);
void    MODE(Command &command);
void    PING(Command &command);
void	PRIVMSG(Command& command);
void    NOTICE(Command& command);
void    QUIT(Command& command);
void    WHOIS(Command& command);
void    WHOWAS(Command& command);
void    OPER(Command& command);
void    KILL(Command& command);
void    JOIN(Command& command);

// Replies not in RFC
std::string	RPL_PONG(std::vector<std::string> args);
std::string RPL_PRIVMSG(std::vector<std::string> args);
std::string RPL_QUIT(std::vector<std::string> args);
std::string RPL_KILL(std::vector<std::string> args);

// Replies
std::string	RPL_WELCOME(std::vector<std::string> args);
std::string	RPL_UMODEIS(std::vector<std::string> args);
std::string	RPL_AWAY(std::vector<std::string> args);
std::string	RPL_WHOISUSER(std::vector<std::string> args);
std::string	RPL_WHOISSERVER(std::vector<std::string> args);
std::string	RPL_WHOISOPERATOR(std::vector<std::string> args);
std::string	RPL_WHOWASUSER(std::vector<std::string> args);
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
std::string	RPL_ENDOFWHOWAS(std::vector<std::string> args);
std::string RPL_WHOISHOST(std::vector<std::string> args);
std::string RPL_WHOISMODES(std::vector<std::string> args);
std::string	RPL_YOUREOPER(std::vector<std::string> args);
std::string	RPL_USERSSTART(std::vector<std::string> args);
std::string	RPL_USERS(std::vector<std::string> args);
std::string	RPL_ENDOFUSERS(std::vector<std::string> args);
std::string	RPL_NOUSERS(std::vector<std::string> args);

// Errors
std::string	ERR_NOSUCHNICK(std::vector<std::string> args);
std::string	ERR_NOSUCHSERVER(std::vector<std::string> args);
std::string	ERR_NOSUCHCHANNEL(std::vector<std::string> args);
std::string	ERR_CANNOTSENDTOCHAN(std::vector<std::string> args);
std::string	ERR_TOOMANYCHANNELS(std::vector<std::string> args);
std::string	ERR_WASNOSUCHNICK(std::vector<std::string> args);
std::string	ERR_TOOMANYTARGETS(std::vector<std::string> args);
std::string	ERR_NOORIGIN(std::vector<std::string> args);
std::string	ERR_NORECIPIENT(std::vector<std::string> args);
std::string	ERR_NOTEXTTOSEND(std::vector<std::string> args);
std::string	ERR_NOTOPLEVEL(std::vector<std::string> args);
std::string	ERR_WILDTOPLEVEL(std::vector<std::string> args);
std::string	ERR_FILEERROR(std::vector<std::string> args);
std::string	ERR_NONICKNAMEGIVEN(std::vector<std::string> args);
std::string	ERR_ERRONEUSNICKNAME(std::vector<std::string> args);
std::string	ERR_NICKNAMEINUSE(std::vector<std::string> args);
std::string	ERR_NICKCOLLISION(std::vector<std::string> args);
std::string	ERR_UNAVAILRESOURCE(std::vector<std::string> args);
std::string	ERR_USERNOTINCHANNEL(std::vector<std::string> args);
std::string	ERR_NOTONCHANNEL(std::vector<std::string> args);
std::string	ERR_USERONCHANNEL(std::vector<std::string> args);
std::string	ERR_USERSDISABLED(std::vector<std::string> args);
std::string	ERR_NEEDMOREPARAMS(std::vector<std::string> args);
std::string	ERR_ALREADYREGISTRED(std::vector<std::string> args);
std::string	ERR_PASSWDMISMATCH(std::vector<std::string> args);
std::string	ERR_CHANNELISFULL(std::vector<std::string> args);
std::string	ERR_INVITEONLYCHAN(std::vector<std::string> args);
std::string	ERR_BANNEDFROMCHAN(std::vector<std::string> args);
std::string	ERR_BADCHANNELKEY(std::vector<std::string> args);
std::string	ERR_BADCHANMASK(std::vector<std::string> args);
std::string	ERR_NOCHANMODES(std::vector<std::string> args);
std::string	ERR_CHANOPRIVSNEEDED(std::vector<std::string> args);
std::string	ERR_RESTRICTED(std::vector<std::string> args);
std::string	ERR_NOOPERHOST(std::vector<std::string> args);
std::string	ERR_UMODEUNKNOWNFLAG(std::vector<std::string> args);
std::string	ERR_USERSDONTMATCH(std::vector<std::string> args);
std::string	ERR_NOPRIVILEGES(std::vector<std::string> args);
std::string	ERR_CANTKILLSERVER(std::vector<std::string> args);

#endif