/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:33 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/19 15:00:24 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
# include "Logger.hpp"
# include <iostream>
# include <string>
# include <vector>
# include <map>

class Server;

class User;

class Command
{
public:
	// Constructors and destructor
								Command(void);
								Command(User* user, std::string command_line,
									Server* server);
								Command(const Command& src);
								~Command(void);

	// Operators
	Command& 					operator=(const Command& rhs);

	// Getters
	std::string					getLine(void) const;
	std::string 				getPrefix(void) const;
	std::string 				getCommand(void) const;
	std::vector<std::string>	getParameters(void) const;
	std::string 				getTrailer(void) const;
	User&						getUser(void) const;
	User*						getUser(std::string nickname);
	std::vector<User *>*		getUsers(void);


	// Replies functions
	void						replyTo(User *user, int code,
									std::vector<std::string> args
									= std::vector<std::string>());
	void						replyAll(int code,
									std::vector<std::string> args
									= std::vector<std::string>());
	void						reply(int code, std::vector<std::string> args
									= std::vector<std::string>());
private:
	std::string 				_prefix;
	std::string 				_command;
	std::vector<std::string>	_parameters;
	std::string 				_trailer;
	std::string 				_command_line;
	User*						_user;
	Server*						_server;
};

std::ostream &  operator<<(std::ostream & o, Command const & rhs);


#endif