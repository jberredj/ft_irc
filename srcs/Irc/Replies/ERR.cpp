/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 07:38:25 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/17 12:25:45 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>

std::string	ERR_NOSUCHNICK(std::vector<std::string> args)
{
	std::string&	nickname = args[0];

	return nickname + " :No such nick";
}

std::string	ERR_NOSUCHSERVER(std::vector<std::string> args)
{
	std::string&	serverName = args[0];

	return serverName + " :No such server";
}

std::string	ERR_NOSUCHCHANNEL(std::vector<std::string> args)
{
	std::string&	channelName = args[0];

	return channelName + " :No such channel";
}

std::string	ERR_CANNOTSENDTOCHAN(std::vector<std::string> args)
{
	std::string&	channelName = args[0];

	return channelName + " :Cannot send to channel";
}

std::string	ERR_TOOMANYCHANNELS(std::vector<std::string> args)
{
	std::string&	channelName = args[0];

	return channelName + " :You have joined too many channels";
}

std::string	ERR_TOOMANYTARGETS(std::vector<std::string> args)
{
	std::string&	target = args[0];

	return target + " :Duplicate recipients. No message delivered";
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

std::string	ERR_NOTOPLEVEL(std::vector<std::string> args)
{
	std::string&	mask = args[0];

	return mask + " :No toplevel domain specified";
}

std::string	ERR_WILDTOPLEVEL(std::vector<std::string> args)
{
	std::string&	mask = args[0];

	return mask + " :Wildcard in toplevel domain";
}

std::string	ERR_FILEERROR(std::vector<std::string> args)
{
	std::string&	fileOperation = args[0];
	std::string&	file = args[1];

	return ":File error doing " + fileOperation + " on " + file;
}

std::string	ERR_NONICKNAMEGIVEN(std::vector<std::string> args)
{
	(void)args;
	return ":No nickname given";
}

std::string	ERR_ERRONEUSNICKNAME(std::vector<std::string> args)
{
	std::string&	nickname = args[0];

	return nickname + " :Erroneous nickname";
}

std::string	ERR_NICKNAMEINUSE(std::vector<std::string> args)
{
	std::string&	nickname = args[0];

	return nickname + " :Nickname is already in use";
}

std::string	ERR_NICKCOLLISION(std::vector<std::string> args)
{
	std::string&	nickname = args[0];
	std::string&	user = args[1];
	std::string&	host = args[2];

	return nickname + " :Nickname collision KILL from "
			+ user + "@" + host;
}

std::string	ERR_UNAVAILRESOURCE(std::vector<std::string> args)
{
	std::string&	nicknameOrChannel = args[0];

	return nicknameOrChannel + " :Nick/channel is temporarily unavailable";
}

std::string	ERR_USERNOTINCHANNEL(std::vector<std::string> args)
{
	std::string&	nickname = args[0];
	std::string&	channel = args[1];

	return nickname + " " + channel + " :They aren't on that channel";
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

std::string	ERR_USERSDISABLED(std::vector<std::string> args)
{
	(void)args;
	return ":USERS has been disabled";
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

std::string	ERR_INVITEONLYCHAN(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :Cannot join channel (+i)";
}

std::string	ERR_BANNEDFROMCHAN(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :Cannot join channel (+b)";
}

std::string	ERR_BADCHANNELKEY(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :Cannot join channel (+k)";
}

std::string	ERR_BADCHANMASK(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :Bad Channel Mask";
}

std::string	ERR_NOCHANMODES(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :Channel doesn't support modes";
}

std::string	ERR_CHANOPRIVSNEEDED(std::vector<std::string> args)
{
	std::string&	channel = args[0];

	return channel + " :You're not channel operator";
}

std::string	ERR_RESTRICTED(std::vector<std::string> args)
{
	(void)args;
	return ":Your connection is restricted!";
}

std::string	ERR_NOOPERHOST(std::vector<std::string> args)
{
	(void)args;
	return ":No O-lines for your host";
}

std::string	ERR_UMODEUNKNOWNFLAG(std::vector<std::string> args)
{
	(void)args;
	return ":Unknown MODE flag";
}

std::string	ERR_USERSDONTMATCH(std::vector<std::string> args)
{
	(void)args;
	return ":Cannot change mode for other users";
}
