/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:08:26 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/12 18:44:53 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

std::string	RPL_PONG(std::vector<std::string> args)
{
	return args[0] + ":" + args[1];
}

std::string RPL_PRIVMSG(std::vector<std::string> args)
{
	return "PRIVMSG " + args[0] + " :" + args[1];
}

std::string RPL_QUIT(std::vector<std::string> args)
{
	return "ERROR :Closing link: (" + args[0] + "@" + args[1] + ") [Quit: " + args[2] + "]";
}

std::string	RPL_WELCOME(std::vector<std::string> args)
{
	return "Welcome to the Internet Relay Network " 
		+ args[0] + "!" + args[1] + "@" + args[2];
}

std::string	RPL_UMODEIS(std::vector<std::string> args)
{
	return args[0];
}

std::string	RPL_AWAY(std::vector<std::string> args)
{
	return args[0] + " :" + args[1];
}

std::string	RPL_WHOISUSER(std::vector<std::string> args)
{
	std::string &nick = args[0];
	std::string &user = args[1];
	std::string &host = args[2];
	std::string &real = args[3];

	return nick + " " + user + " " + host + " * :" + real;
}

std::string	RPL_WHOISSERVER(std::vector<std::string> args)
{
	std::string &nick = args[0];
	std::string &server = args[1];
	std::string &server_info = args[2];

	return nick + " " + server + " :" + server_info;
}

std::string	RPL_WHOISOPERATOR(std::vector<std::string> args)
{
	std::string &nick = args[0];

	return nick + " :is an IRC operator";
}

std::string	RPL_WHOISIDLE(std::vector<std::string> args)
{
	std::string &nick = args[0];
	std::string &integer = args[1];

	return  nick + " " + integer + " :seconds idle";
}

std::string	RPL_WHOISHOST(std::vector<std::string> args)
{
	std::string &nick = args[0];
	std::string &user = args[1];
	std::string &host = args[2];
	std::string &ipstring = args[3];

	return  nick + " :is connecting from " + user + "@" + host + " " + ipstring; 
}

std::string	RPL_WHOISMODES(std::vector<std::string> args)
{
	std::string &nick = args[0];
	std::string &mode = args[1];

	// TODO ? seems to be another parameter called snomaskmode->GetUserParameter(dest) 
	// if mode is set to `snomaskmode` ? https://github.com/inspircd/inspircd/blob/insp3/src/coremods/core_whois.cpp l.244

	return  nick + " :is using mode +" + mode;
}

std::string	RPL_ENDOFWHOIS(std::vector<std::string> args)
{
	std::string &nick = args[0];

	return nick + " :End of /WHOIS list";
}

std::string	RPL_WHOISCHANNELS(std::vector<std::string> args)
{
	// "<nick> :{[@|+]<channel><space>}" @ + Indicate user mod or allow to speak on mod chan, Handle that in getReplies/generateReply Wrapper
	std::string	reply = args[0] + " :";
	for(std::vector<std::string>::iterator it = args.begin() + 1;
		it != args.end(); it++)
		reply += *it + " ";
	return reply;
}

std::string	RPL_LISTSTART(std::vector<std::string> args)
{
	(void)args;
	return "Channel :Users  Name";
}

std::string	RPL_LIST(std::vector<std::string> args)
{
	// "<channel> <NbrChannelMembers> :<topic>"
	return args[0] + " " + args[1] + " :" + args[2];
}

std::string	RPL_LISTEND(std::vector<std::string> args)
{
	(void)args;
	return ":End of /LIST";
}

std::string	RPL_NOTOPIC(std::vector<std::string> args)
{
	return args[0] + " :No topic is set";
}

std::string	RPL_TOPIC(std::vector<std::string> args)
{
	return args[0] + " :" + args[1];
}

std::string	RPL_INVITING(std::vector<std::string> args)
{
	return args[0] + " " + args[1];
}

std::string	RPL_NAMREPLY(std::vector<std::string> args)
{
	std::string	reply = args[0] + " :";
	for (std::vector<std::string>::iterator it = args.begin() +1;
		it != args.end(); it++)
		reply += *it + " ";
	return reply;
}

std::string	RPL_ENDOFNAMES(std::vector<std::string> args)
{
	return args[0] + " :End of NAMES list";
}

std::string	RPL_YOUREOPER(std::vector<std::string> args)
{
	(void)args;
	return ":You are now an IRC operator";
}

std::string	RPL_USERSSTART(std::vector<std::string> args)
{
	(void)args;
	return ":UserID   Terminal  Host";
}

std::string	RPL_USERS(std::vector<std::string> args)
{
	return ":" + args[0] + " " + args[1] + " " + args[2];
}

std::string	RPL_ENDOFUSERS(std::vector<std::string> args)
{
	(void)args;
	return ":End of users";
}

std::string	RPL_NOUSERS(std::vector<std::string> args)
{
	(void)args;
	return ":Nobody logged in";
}
