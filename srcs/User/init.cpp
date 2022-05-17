/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <esommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:09:13 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/17 13:37:57 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "User.hpp"
#include "Command.hpp"
#include "IrcMessages.hpp"

void WHOIS(Command &command){(void)command;}
void USERS(Command &command){(void)command;}
// void USER(Command &command){(void)command;}
void TOPIC(Command &command){(void)command;}
void PRIVMSG(Command &command){(void)command;}
void PONG(Command &command){(void)command;}
void PING(Command &command){(void)command;}
void PART(Command &command){(void)command;}
void OPER(Command &command){(void)command;}
void NICK(Command &command){(void)command;}
void NAMES(Command &command){(void)command;}
void MODE(Command &command){(void)command;}
void LIST(Command &command){(void)command;}
void KILL(Command &command){(void)command;}
void KICK(Command &command){(void)command;}
void JOIN(Command &command){(void)command;}
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
		Logger(Output::WARN) << "WHOIS message is not implemented yet";
		_cmdMap["USERS"] = USERS;
		Logger(Output::WARN) << "USERS message is not implemented yet";
		_cmdMap["USER"] = USER;
		// Logger(Output::WARN) << "USER message is not implemented yet";
		_cmdMap["TOPIC"] = TOPIC;
		Logger(Output::WARN) << "TOPIC message is not implemented yet";
		_cmdMap["PRIVMSG"] = PRIVMSG;
		Logger(Output::WARN) << "PRIVMSG message is not implemented yet";
		_cmdMap["PONG"] = PONG;
		Logger(Output::WARN) << "PONG message is not implemented yet";
		_cmdMap["PPING"] = PING;
		Logger(Output::WARN) << "PING message is not implemented yet";
		_cmdMap["PASS"] = PASS;
		_cmdMap["PART"] = PART;
		Logger(Output::WARN) << "PART message is not implemented yet";
		_cmdMap["OPER"] = OPER;
		Logger(Output::WARN) << "OPER message is not implemented yet";
		_cmdMap["NICK"] = NICK;
		Logger(Output::WARN) << "NICK message is not implemented yet";
		_cmdMap["NAMES"] = NAMES;
		Logger(Output::WARN) << "NAMES message is not implemented yet";
		_cmdMap["MODE"] = MODE;
		Logger(Output::WARN) << "MODE message is not implemented yet";
		_cmdMap["LIST"] = LIST;
		Logger(Output::WARN) << "LIST message is not implemented yet";
		_cmdMap["KILL"] = KILL;
		Logger(Output::WARN) << "KILL message is not implemented yet";
		_cmdMap["KICK"] = KICK;
		Logger(Output::WARN) << "KICK message is not implemented yet";
		_cmdMap["JOIN"] = JOIN;
		Logger(Output::WARN) << "JOIN message is not implemented yet";
		_cmdMap["INVITE"] = INVITE;
		Logger(Output::WARN) << "INVITE message is not implemented yet";
		_cmdMap["BAN"] = BAN;
		Logger(Output::WARN) << "BAN message is not implemented yet";
		Logger(Output::TRACE) << "User command map initiated";
	}
}

// Init static var
std::map<std::string, void (*)(Command&)> User::_cmdMap;