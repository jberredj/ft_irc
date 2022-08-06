/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:09:13 by jberredj          #+#    #+#             */
/*   Updated: 2022/07/27 02:32:16 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"


/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

void	User::_initUserClass(void)
{
	if (_cmdMap.empty())
	{
		_cmdMap["WHOIS"] = WHOIS;
		_cmdMap["WHOWAS"] = WHOWAS;
		_cmdMap["USER"] = USER;
		_cmdMap["TOPIC"] = TOPIC;
		_cmdMap["PRIVMSG"] = PRIVMSG;
		_cmdMap["NOTICE"] = NOTICE;
		_cmdMap["QUIT"] = QUIT;
		_cmdMap["PONG"] = PONG;
		_cmdMap["PING"] = PING;
		_cmdMap["PASS"] = PASS;
		_cmdMap["PART"] = PART;
		_cmdMap["OPER"] = OPER;
		_cmdMap["NICK"] = NICK;
		_cmdMap["NAMES"] = NAMES;
		Logger(Output::WARN) << "NAMES: Check correct error Cases";
		_cmdMap["MODE"] = MODE;
		_cmdMap["LIST"] = LIST;
		_cmdMap["KILL"] = KILL;
		_cmdMap["KICK"] = KICK;
		_cmdMap["JOIN"] = JOIN;
		_cmdMap["INVITE"] = INVITE;
		_cmdMap["AWAY"] = AWAY;
	}
}

// Init static var
std::map<std::string, void (*)(Command&)> User::_cmdMap;