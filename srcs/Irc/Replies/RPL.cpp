/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:08:26 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/15 18:45:56 by ddiakova         ###   ########.fr       */
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

std::string RPL_KILL(std::vector<std::string> args)
{
	return args[0] + " has quit [" + args[1] + " ]";
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
	return args[0] + " " + args[1] + " " + args[2] + " * :" + args[3];
}

std::string	RPL_WHOISSERVER(std::vector<std::string> args)
{
	return args[0] + " " + args[1] + " :" + args[2];
}

std::string	RPL_WHOISOPERATOR(std::vector<std::string> args)
{
	return args[0] + " :is an IRC operator";
}

std::string	RPL_WHOISIDLE(std::vector<std::string> args)
{
	return  args[0] + " " + args[1] +" :seconds idle";
}

std::string	RPL_ENDOFWHOIS(std::vector<std::string> args)
{
	return args[0] + " :End of WHOIS list";
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
