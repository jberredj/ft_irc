/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:33 by ddiakova          #+#    #+#             */
/*   Updated: 2022/07/06 21:05:58 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
# include "Logger.hpp"
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include "Channel.hpp"
# include "typedefs.hpp"

class Server;

class User;

class Command
{
public:
	// Constructors and destructor
								Command(void);
								Command(User* user, std::string command_line, Server* server);
								Command(const Command& src);
								~Command(void);

	// Operators
	Command& 					operator=(const Command& rhs);

	// Getters
	std::string					getLine(void) const;
	std::string 				getPrefix(void) const;
	std::string 				getCommand(void) const;
	const strVec				&getParameters(void) const;
	std::string 				getTrailer(void) const;
	User&						getInvoker(void) const;
	User*						getUser(std::string nickname) const;
	User*						getUserFromName(std::string username) const;
	std::vector<User *>*		getUsers(void);
	// Server*						getServer(void) const;
	std::string					getServerPassword(void) const;
	User*						getOldUser(std::string nickname);
	std::vector<User *>*		getOldUsers(void);
	std::string					getServerName(void) const;
	Channel*					getChannel(std::string name);
	std::map<std::string, Channel*>*	getChannels(void);
	void						addChannel(Channel *channel);
	bool						targetsInvoker(void) const;
	bool						existingTarget(void) const;

	// Replies functions
	void		replyAllReachable(std::string message);
	void		replyAllReachable(int code, strVec args);
	void		replyAll(std::string message);
	void		replyAll(int code, strVec args);
	void		replyToInvoker(int code, strVec args = strVec());
	void		invokerSendTo(User* receiver, int code, strVec args = strVec());

private:
	std::string _prefix;
	std::string	_command;
	strVec		_parameters;
	std::string _trailer;
	std::string _command_line;
	User*		_invoker;
	Server*		_server;

	// Replies functions
	std::string	_reply(User* sender, User* receiver, int code, strVec args = strVec());
};

std::ostream &  operator<<(std::ostream & o, Command const & rhs);


#endif