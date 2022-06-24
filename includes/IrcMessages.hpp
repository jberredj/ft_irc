/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessages.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:52:17 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/23 10:46:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGES_HPP
# define IRCMESSAGES_HPP
# include "Command.hpp"
# include "typedefs.hpp"
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
void    AWAY(Command& command);
void	PART(Command &command);

// Replies not in RFC
std::string	RPL_PONG(strVec args);
std::string RPL_PRIVMSG(strVec args);
std::string RPL_QUIT(strVec args);
std::string RPL_KILL(strVec args);
std::string RPL_SETUSERMODE(strVec args);

// Replies
std::string	RPL_WELCOME(strVec args);
std::string	RPL_UMODEIS(strVec args);
std::string	RPL_AWAY(strVec args);
std::string	RPL_UNAWAY(strVec args);
std::string	RPL_NOWAWAY(strVec args);
std::string	RPL_WHOISUSER(strVec args);
std::string	RPL_WHOISSERVER(strVec args);
std::string	RPL_WHOISOPERATOR(strVec args);
std::string	RPL_WHOWASUSER(strVec args);
std::string	RPL_WHOISIDLE(strVec args);
std::string	RPL_ENDOFWHOIS(strVec args);
std::string	RPL_WHOISCHANNELS(strVec args);
std::string	RPL_LISTSTART(strVec args);
std::string	RPL_LIST(strVec args);
std::string	RPL_LISTEND(strVec args);
std::string	RPL_NOTOPIC(strVec args);
std::string	RPL_TOPIC(strVec args);
std::string	RPL_INVITING(strVec args);
std::string	RPL_NAMREPLY(strVec args);
std::string	RPL_ENDOFNAMES(strVec args);
std::string	RPL_ENDOFWHOWAS(strVec args);
std::string RPL_WHOISHOST(strVec args);
std::string RPL_WHOISMODES(strVec args);
std::string	RPL_YOUREOPER(strVec args);
std::string	RPL_USERSSTART(strVec args);
std::string	RPL_USERS(strVec args);
std::string	RPL_ENDOFUSERS(strVec args);
std::string	RPL_NOUSERS(strVec args);

// Errors
std::string	ERR_NOSUCHNICK(strVec args);
std::string	ERR_NOSUCHSERVER(strVec args);
std::string	ERR_NOSUCHCHANNEL(strVec args);
std::string	ERR_CANNOTSENDTOCHAN(strVec args);
std::string	ERR_TOOMANYCHANNELS(strVec args);
std::string	ERR_WASNOSUCHNICK(strVec args);
std::string	ERR_TOOMANYTARGETS(strVec args);
std::string	ERR_NOORIGIN(strVec args);
std::string	ERR_NORECIPIENT(strVec args);
std::string	ERR_NOTEXTTOSEND(strVec args);
std::string	ERR_NOTOPLEVEL(strVec args);
std::string	ERR_WILDTOPLEVEL(strVec args);
std::string	ERR_FILEERROR(strVec args);
std::string	ERR_NONICKNAMEGIVEN(strVec args);
std::string	ERR_ERRONEUSNICKNAME(strVec args);
std::string	ERR_NICKNAMEINUSE(strVec args);
std::string	ERR_NICKCOLLISION(strVec args);
std::string	ERR_UNAVAILRESOURCE(strVec args);
std::string	ERR_USERNOTINCHANNEL(strVec args);
std::string	ERR_NOTONCHANNEL(strVec args);
std::string	ERR_USERONCHANNEL(strVec args);
std::string	ERR_USERSDISABLED(strVec args);
std::string	ERR_NEEDMOREPARAMS(strVec args);
std::string	ERR_ALREADYREGISTRED(strVec args);
std::string	ERR_PASSWDMISMATCH(strVec args);
std::string	ERR_CHANNELISFULL(strVec args);
std::string	ERR_INVITEONLYCHAN(strVec args);
std::string	ERR_BANNEDFROMCHAN(strVec args);
std::string	ERR_BADCHANNELKEY(strVec args);
std::string	ERR_BADCHANMASK(strVec args);
std::string	ERR_NOCHANMODES(strVec args);
std::string	ERR_CHANOPRIVSNEEDED(strVec args);
std::string	ERR_RESTRICTED(strVec args);
std::string	ERR_NOOPERHOST(strVec args);
std::string	ERR_UMODEUNKNOWNFLAG(strVec args);
std::string	ERR_USERSDONTMATCH(strVec args);
std::string	ERR_NOPRIVILEGES(strVec args);
std::string	ERR_CANTKILLSERVER(strVec args);

#endif