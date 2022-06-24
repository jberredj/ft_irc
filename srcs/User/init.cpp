/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:09:13 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/24 15:13:19 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void USERS(Command &command){(void)command;}
void PONG(Command &command){(void)command;}
void NAMES(Command &command){(void)command;}
void LIST(Command &command){(void)command;}
void KICK(Command &command){(void)command;}
void INVITE(Command &command){(void)command;}
void BAN(Command &command){(void)command;}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

void	User::_initUserClass(void)
{
	if (_cmdMap.empty())
	{
		_cmdMap["WHOIS"] = WHOIS;
		_cmdMap["WHOWAS"] = WHOWAS;
		_cmdMap["USERS"] = USERS;
		Logger(Output::WARN) << "USERS message is not implemented yet";
		_cmdMap["USER"] = USER;
		_cmdMap["TOPIC"] = TOPIC;
		Logger(Output::WARN) << "TOPIC message is not implemented yet";
		_cmdMap["PRIVMSG"] = PRIVMSG;
		Logger(Output::INFO) << "PRIVMSG message is incomplete";
		_cmdMap["NOTICE"] = NOTICE;
		Logger(Output::INFO) << "NOTICE message may be incomplete";
		_cmdMap["QUIT"] = QUIT;
		_cmdMap["PONG"] = PONG;
		Logger(Output::WARN) << "PONG message is not implemented yet";
		_cmdMap["PING"] = PING;
		_cmdMap["PASS"] = PASS;
		_cmdMap["PART"] = PART;
		_cmdMap["OPER"] = OPER;
		// Logger(Output::WARN) << "OPER message is not implemented yet";
		_cmdMap["NICK"] = NICK;
		_cmdMap["NAMES"] = NAMES;
		Logger(Output::WARN) << "NAMES message is not implemented yet";
		_cmdMap["MODE"] = MODE;
		Logger(Output::WARN) << "MODE message is not implemented yet";
		_cmdMap["LIST"] = LIST;
		Logger(Output::WARN) << "LIST message is not implemented yet";
		_cmdMap["KILL"] = KILL;
		// Logger(Output::WARN) << "KILL message is not implemented yet";
		_cmdMap["KICK"] = KICK;
		Logger(Output::WARN) << "KICK message is not implemented yet";
		_cmdMap["JOIN"] = JOIN;
		Logger(Output::WARN) << "JOIN message is not implemented yet";
		_cmdMap["INVITE"] = INVITE;
		Logger(Output::WARN) << "INVITE message is not implemented yet";
		_cmdMap["BAN"] = BAN;
		Logger(Output::WARN) << "BAN NOT IN RFC 1459. USE MODE <channe> +b <target> INSTEAD. BAN message is not implemented yet";
		Logger(Output::TRACE) << "User command map initiated";
		_cmdMap["AWAY"] = AWAY;
		// Logger(Output::WARN) << "INVITE message is not implemented yet";
	}
}

// Init static var
std::map<std::string, void (*)(Command&)> User::_cmdMap;