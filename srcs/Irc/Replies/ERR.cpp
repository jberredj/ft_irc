/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 07:38:25 by jberredj          #+#    #+#             */
/*   Updated: 2022/08/06 18:34:35 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>

std::string	ERR_NOSUCHNICK(std::vector<std::string> args)
{
	std::string&	nickname = args[0];

	return nickname + " :No such nick";
}

std::string	ERR_NOSUCHCHANNEL(std::vector<std::string> args)
{
	std::string&	channelName = args[0];

	return channelName + " :No such channel";
}

std::string	ERR_CANNOTSENDTOCHAN(std::vector<std::string> args)
{
	std::string&	channelName = args[0];

	return channelName + " :You cannot send external messages to this channel whilst the +n (noextmsg) mode is set.";
}

std::string	ERR_WASNOSUCHNICK(std::vector<std::string> args)
{
	std::string&	nick = args[0];

	return nick + " :There was no such nickname";
}

std::string	ERR_NOORIGIN(std::vector<std::string> args)
{
	(void)args;
	return ":No origin specified";
}

std::string	ERR_NORECIPIENT(std::vector<std::string> args)
{
	std::string&	command = args[0];

	return ":No recipient given (" + command + ")";
}

std::string	ERR_NOTEXTTOSEND(std::vector<std::string> args)
{
	(void)args;
	return ":No text to send";
}

std::string	ERR_NONICKNAMEGIVEN(std::vector<std::string> args)
{
	(void)args;
	return ":No nickname given";
}

std::string	ERR_ERRONEUSNICKNAME(std::vector<std::string> args)
{
	std::string&	nickname = args[0];

	return nickname + " :Erroneous Nickname";
}

std::string	ERR_NICKNAMEINUSE(std::vector<std::string> args)
{
	std::string&	nickname = args[0];

	return nickname + " :Nickname is already in use.";
}

std::string	ERR_NOTONCHANNEL(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :You're not on that channel";
}

std::string	ERR_USERONCHANNEL(std::vector<std::string> args)
{
	std::string&	user = args[0];
	std::string&	channel = args[1];

	return user + " " + channel + " :is already on channel";
}

std::string ERR_NOTREGISTERED(std::vector<std::string> args)
{
	(void)args;
	return ":You have not registered";
}

std::string	ERR_NEEDMOREPARAMS(std::vector<std::string> args)
{
	std::string	command = args[0];

	return command + " :Not enough parameters";
}

std::string	ERR_ALREADYREGISTRED(std::vector<std::string> args)
{
	(void)args;
	return ":You may not reregister";
}

std::string	ERR_PASSWDMISMATCH(std::vector<std::string> args)
{
	(void)args;
	return ":Password incorrect";
}

std::string	ERR_CHANNELISFULL(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :Cannot join channel (+l)";
}

std::string	ERR_UNKNOWNMODE(std::vector<std::string> args)
{
	std::string mode = args[0];
	return mode + " :is not a recognised channel mode.";
}

std::string	ERR_INVITEONLYCHAN(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :Cannot join channel (invite only)";
}


std::string	ERR_CHANOPRIVSNEEDED(std::vector<std::string> args)
{
	// #tardis :You must be a channel halfop or higher to set channel mode n (noextmsg).
	std::string channelName = args[0];
	std::string lvlop = args[1];
	std::string mode = args[2];
	std::string description = args[3];

	return channelName + " :You must be a channel " + lvlop + 
			" or higher to set channel mode " + mode + " (" + description + ").";
}

std::string	ERR_UMODEUNKNOWNFLAG(std::vector<std::string> args)
{
	(void)args;
	return ":Unknown MODE flag";
}

std::string	ERR_USERSDONTMATCH(std::vector<std::string> args)
{
	std::string msg = args[0];
	return ":" + msg + " for other users";
}

std::string	ERR_NOPRIVILEGES(std::vector<std::string> args)
{
	(void)args;
	return ":Permission Denied- You're not an IRC operator";
}

std::string	ERR_CMODEMISSINGPARAMETER(std::vector<std::string> args)
{
	// #tardis l * :You must specify a parameter for the limit mode. Syntax: <limit>.
	// #tardis o * :You must specify a parameter for the op mode. Syntax: <nick>.
	std::string channelName = args[0];
	std::string shortMode = args[1];
	std::string longMode = args[2];
	std::string syntax = args[3];

	return channelName + " " + shortMode + " * :You must specify a parameter for the "
			+ longMode + " mode. Syntax: <" + syntax + ">.";
}