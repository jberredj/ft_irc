/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:08:26 by jberredj          #+#    #+#             */
/*   Updated: 2022/08/06 18:19:53 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcMessages.hpp"

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

std::string RPL_NOTICE(strVec args)
{
	std::string	target = args[0];
	std::string	message = args[1];
	return "NOTICE " + target + " :" + message;
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

std::string RPL_SETUSERMODE(strVec args)
{
	std::string nickname = args[0];
	std::string changes = args[1];
	return "MODE " + nickname + " :" + changes;
}

std::string	RPL_WELCOME(strVec args)
{
	std::string	prefix = args[0];
	return "Welcome to the Internet Relay Network " + prefix;
}

std::string RPL_ACCESSDENIED(strVec args)
{
	std::string	username = args[0];
	std::string host = args[1];
	return "ERROR :Closing link: (" + username + "@" + host + ") [Access denied by configuration]";
}
std::string	RPL_UMODEIS(strVec args)
{
	std::string	modeString = args[0];
	return ":+" + modeString;
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
	std::string	topic;
	if (args.size() > 2) 
		topic = args[2];
	return channel + " " + nbrMember + (topic.empty() ? "" : " :" + topic);
}

std::string	RPL_LISTEND(strVec args)
{
	(void)args;
	return ":End of /LIST";
}

std::string	RPL_CHANNELMODEIS(strVec args)
{
	std::string channelName = args[0];
	std::string	modeString = args[1];
	return channelName + " :+" + modeString;
}

std::string	RPL_CREATIONTIME(strVec args)
{
	std::string channelName = args[0];
	std::string creationTime = args[1];
	return channelName + " :" + creationTime;
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
	std::string	reply = "= " + channel + " :";
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

std::string	RPL_SETNEWNICK(strVec args)
{
	std::string &nick = args[0];

	return "NICK :" + nick;
}