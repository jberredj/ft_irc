/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:08:26 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/23 10:46:46 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.hpp"
#include "Command.hpp"

std::string	RPL_PONG(strVec args)
{
	std::string	userPrefix = args[0];
	std::string	payload = args[1];
	return userPrefix + " :" + payload;
}

std::string RPL_PRIVMSG(strVec args)
{
	std::string	target = args[0];
	std::string	message = args[1];
	return "PRIVMSG " + target + " :" + message;
}

std::string RPL_QUIT(strVec args)
{
	std::string	username = args[0];
	std::string host = args[1];
	std::string	message = args[2];
	return "ERROR :Closing link: (" + username + "@" + host + ") [" + message + "]";
}

std::string RPL_KILL(strVec args)
{
	std::string	nickname = args[0];
	std::string	reason = args[1];
	return nickname + " has quit [" + reason + "]";
}

std::string	RPL_WELCOME(strVec args)
{
	std::string	prefix = args[0];
	return "Welcome to the Internet Relay Network " + prefix;
}

std::string	RPL_UMODEIS(strVec args)
{
	std::string	modeString = args[0];
	return modeString;
}

std::string	RPL_AWAY(strVec args)
{
	std::string nickname = args[0];
	std::string	message = args[1];
	return nickname + " :" + message;
}

std::string	RPL_UNAWAY(strVec args)
{
	(void)args;
	return ":You are no longer marked as being away";
}

std::string	RPL_NOWAWAY(strVec args)
{
	(void)args;
	return ":You have been marked as being away";
}

std::string	RPL_WHOISUSER(strVec args)
{
	std::string &nick = args[0];
	std::string &user = args[1];
	std::string &host = args[2];
	std::string &real = args[3];

	return nick + " " + user + " " + host + " * :" + real;
}

std::string	RPL_WHOISSERVER(strVec args)
{
	std::string &nick = args[0];
	std::string &server = args[1];
	std::string &server_info = args[2];

	return nick + " " + server + " :" + server_info;
}

std::string	RPL_WHOISOPERATOR(strVec args)
{
	std::string &nick = args[0];

	return nick + " :is an IRC operator";
}

std::string	RPL_WHOWASUSER(strVec args)
{
	std::string &nick = args[0];
	std::string &user = args[1];
	std::string &host = args[2];
	std::string &real = args[3];

	return nick + " " + user + " " + host + " * :" + real;
}

std::string	RPL_WHOISIDLE(strVec args)
{
	std::string &nick = args[0];
	std::string &idle = args[1];
	std::string &signon = args[2];

	return  nick + " " + idle + " " + signon + " :seconds idle, signon time";
}

std::string	RPL_WHOISHOST(strVec args)
{
	std::string &nick = args[0];
	std::string &user = args[1];
	std::string &host = args[2];
	std::string &ipstring = args[3];

	return  nick + " :is connecting from " + user + "@" + host + " " + ipstring; 
}

std::string	RPL_WHOISMODES(strVec args)
{
	std::string &nick = args[0];
	std::string &mode = args[1];

	// TODO ? seems to be another parameter called snomaskmode->GetUserParameter(dest) 
	// if mode is set to `snomaskmode` ? https://github.com/inspircd/inspircd/blob/insp3/src/coremods/core_whois.cpp l.244

	return  nick + " :is using modes +" + mode;
}

std::string	RPL_ENDOFWHOIS(strVec args)
{
	std::string &nick = args[0];

	return nick + " :End of /WHOIS list.";
}

std::string	RPL_WHOISCHANNELS(strVec args)
{
	// "<nick> :{[@|+]<channel><space>}" @ + Indicate user mod or allow to speak on mod chan, Handle that in getReplies/generateReply Wrapper
	std::string channel = args[0];
	std::string	reply = channel + " :";
	for(strVec::iterator nicknameIt = args.begin() + 1; nicknameIt != args.end(); nicknameIt++)
		reply += *nicknameIt + " ";
	return reply;
}

std::string	RPL_LISTSTART(strVec args)
{
	(void)args;
	return "Channel :Users  Name";
}

std::string	RPL_LIST(strVec args)
{
	// "<channel> <NbrChannelMembers> :<topic>"
	std::string	channel = args[0];
	std::string	nbrMember = args[1];
	std::string	topic = args[2];
	return channel + " " + nbrMember + " :" + topic; // TODO Check if topic is passed if no topic is set
}

std::string	RPL_LISTEND(strVec args)
{
	(void)args;
	return ":End of /LIST";
}

std::string	RPL_NOTOPIC(strVec args)
{
	std::string channel	= args[0];
	return channel + " :No topic is set";
}

std::string	RPL_TOPIC(strVec args)
{
	std::string	channel = args[0];
	std::string	topic = args[1];
	return channel + " :" + topic;
}

std::string	RPL_INVITING(strVec args)
{
	std::string	channel = args[0];
	std::string	nickname = args[1];
	return channel + " " + nickname;
}

std::string	RPL_NAMREPLY(strVec args)
{
	std::string	channel = args[0];
	std::string	reply = channel + " :";
	for (strVec::iterator nicknameIt = args.begin() +1;
		nicknameIt != args.end(); nicknameIt++)
		reply += *nicknameIt + " ";
	return reply;
}

std::string	RPL_ENDOFNAMES(strVec args)
{
	std::string channel = args[0];
	return channel + " :End of NAMES list";
}

std::string	RPL_ENDOFWHOWAS(strVec args)
{
	std::string &nick = args[0];

	return nick + " :End of WHOWAS";
}

std::string	RPL_YOUREOPER(strVec args)
{
	(void)args;
	return ":You are now an IRC operator";
}

std::string	RPL_USERSSTART(strVec args)
{
	(void)args;
	return ":UserID   Terminal  Host";
}

// TODO: Are those required ??? Maybe check this 
std::string	RPL_USERS(strVec args)
{
	return ":" + args[0] + " " + args[1] + " " + args[2];
}

std::string	RPL_ENDOFUSERS(strVec args)
{
	(void)args;
	return ":End of users"; 
}

std::string	RPL_NOUSERS(strVec args)
{
	(void)args;
	return ":Nobody logged in";
}
