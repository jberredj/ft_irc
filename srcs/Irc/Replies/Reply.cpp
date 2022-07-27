/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:16:30 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/27 02:12:34 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Logger.hpp"
#include "Reply.hpp"
#include "IrcMessages.hpp"

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// Constructors and destructor
Reply::Reply(void)
{
	_initRepliesMap();
}

Reply::Reply(const Reply &src)
{
	(void)src;
}

Reply::~Reply(void)
{
}

// Operators
Reply	&Reply::operator=(const Reply &rhs)
{
	(void)rhs;
	return *this;
}

// getReply functions
std::string Reply::getReply(int code, std::vector<std::string> args)
{
	std::string reply;

	try
	{
		return _replies[code](args);
	}
	catch(const std::exception& e)
	{
		Logger(Output::ERROR) << e.what();
	}
	return "";
}

std::string Reply::getReply(std::string (*replyFunc)(std::vector<std::string>),
				std::vector<std::string> args)
{
	std::map<int, std::string (*)(std::vector<std::string>)>::iterator it;

	for(it = _replies.begin(); it != _replies.end(); it++)
		if ((*it).second == replyFunc)
			break;
	if (it == _replies.end())
	{
		Logger(Output::ERROR) << "Function is not in valid replies";
		return "";
	}
	try
	{
		return replyFunc(args);
	}
	catch(const std::exception& e)
	{
		Logger(Output::ERROR) << e.what();
	}
	return "";
}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

// Init function
void	Reply::_initRepliesMap(void)
{
	if (_replies.empty())
	{
		// Replies not in RFC
		_replies.insert(std::make_pair(-1, RPL_PONG));
		_replies.insert(std::make_pair(-2, RPL_PRIVMSG));
		_replies.insert(std::make_pair(-3, RPL_QUIT));
		_replies.insert(std::make_pair(-4, RPL_KILL));
		_replies.insert(std::make_pair(-5, RPL_SETUSERMODE));
		_replies.insert(std::make_pair(-6, RPL_ACCESSDENIED));
		_replies.insert(std::make_pair(-7, RPL_SETNEWNICK));
		_replies.insert(std::make_pair(-8, RPL_NOTICE));

		// Replies
		_replies.insert(std::make_pair(001, RPL_WELCOME));
		_replies.insert(std::make_pair(221, RPL_UMODEIS));
		_replies.insert(std::make_pair(301, RPL_AWAY));
		_replies.insert(std::make_pair(305, RPL_UNAWAY));
		_replies.insert(std::make_pair(306, RPL_NOWAWAY));
		_replies.insert(std::make_pair(311, RPL_WHOISUSER));
		_replies.insert(std::make_pair(312, RPL_WHOISSERVER));
		_replies.insert(std::make_pair(313, RPL_WHOISOPERATOR));
		_replies.insert(std::make_pair(314, RPL_WHOWASUSER));
		_replies.insert(std::make_pair(317, RPL_WHOISIDLE));
		_replies.insert(std::make_pair(318, RPL_ENDOFWHOIS));
		_replies.insert(std::make_pair(319, RPL_WHOISCHANNELS));
		_replies.insert(std::make_pair(321, RPL_LISTSTART));
		_replies.insert(std::make_pair(322, RPL_LIST));
		_replies.insert(std::make_pair(323, RPL_LISTEND));
		_replies.insert(std::make_pair(331, RPL_NOTOPIC));
		_replies.insert(std::make_pair(332, RPL_TOPIC));
		_replies.insert(std::make_pair(341, RPL_INVITING));
		_replies.insert(std::make_pair(353, RPL_NAMREPLY));
		_replies.insert(std::make_pair(366, RPL_ENDOFNAMES));
		_replies.insert(std::make_pair(369, RPL_ENDOFWHOWAS));
		_replies.insert(std::make_pair(378, RPL_WHOISHOST));
		_replies.insert(std::make_pair(379, RPL_WHOISMODES));
		_replies.insert(std::make_pair(381, RPL_YOUREOPER));
		_replies.insert(std::make_pair(392, RPL_USERSSTART));
		_replies.insert(std::make_pair(393, RPL_USERS));
		_replies.insert(std::make_pair(394, RPL_ENDOFUSERS));
		_replies.insert(std::make_pair(395, RPL_NOUSERS));
		
		// Errors
		_replies.insert(std::make_pair(401, ERR_NOSUCHNICK));
		_replies.insert(std::make_pair(402, ERR_NOSUCHSERVER));
		_replies.insert(std::make_pair(403, ERR_NOSUCHCHANNEL));
		_replies.insert(std::make_pair(404, ERR_CANNOTSENDTOCHAN));
		_replies.insert(std::make_pair(405, ERR_TOOMANYCHANNELS));
		_replies.insert(std::make_pair(406, ERR_WASNOSUCHNICK));
		_replies.insert(std::make_pair(407, ERR_TOOMANYTARGETS));
		_replies.insert(std::make_pair(409, ERR_NOORIGIN));
		_replies.insert(std::make_pair(411, ERR_NORECIPIENT));
		_replies.insert(std::make_pair(412, ERR_NOTEXTTOSEND));
		_replies.insert(std::make_pair(413, ERR_NOTOPLEVEL));
		_replies.insert(std::make_pair(414, ERR_WILDTOPLEVEL));
		_replies.insert(std::make_pair(424, ERR_FILEERROR));
		_replies.insert(std::make_pair(431, ERR_NONICKNAMEGIVEN));
		_replies.insert(std::make_pair(432, ERR_ERRONEUSNICKNAME));
		_replies.insert(std::make_pair(433, ERR_NICKNAMEINUSE));
		_replies.insert(std::make_pair(436, ERR_NICKCOLLISION));
		_replies.insert(std::make_pair(437, ERR_UNAVAILRESOURCE));
		_replies.insert(std::make_pair(441, ERR_USERNOTINCHANNEL));
		_replies.insert(std::make_pair(442, ERR_NOTONCHANNEL));
		_replies.insert(std::make_pair(443, ERR_USERONCHANNEL));
		_replies.insert(std::make_pair(446, ERR_USERSDISABLED));
		_replies.insert(std::make_pair(451, ERR_NOTREGISTERED));
		_replies.insert(std::make_pair(461, ERR_NEEDMOREPARAMS));
		_replies.insert(std::make_pair(462, ERR_ALREADYREGISTRED));
		_replies.insert(std::make_pair(464, ERR_PASSWDMISMATCH));
		_replies.insert(std::make_pair(471, ERR_CHANNELISFULL));
		_replies.insert(std::make_pair(473, ERR_INVITEONLYCHAN));
		_replies.insert(std::make_pair(474, ERR_BANNEDFROMCHAN));
		_replies.insert(std::make_pair(475, ERR_BADCHANNELKEY));
		_replies.insert(std::make_pair(476, ERR_BADCHANMASK));
		_replies.insert(std::make_pair(477, ERR_NOCHANMODES));
		_replies.insert(std::make_pair(481, ERR_NOPRIVILEGES));
		_replies.insert(std::make_pair(482, ERR_CHANOPRIVSNEEDED));
		_replies.insert(std::make_pair(483, ERR_CANTKILLSERVER));
		_replies.insert(std::make_pair(484, ERR_RESTRICTED));
		_replies.insert(std::make_pair(491, ERR_NOOPERHOST));
		_replies.insert(std::make_pair(501, ERR_UMODEUNKNOWNFLAG));
		_replies.insert(std::make_pair(502, ERR_USERSDONTMATCH));
	}
}