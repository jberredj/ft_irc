/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:33 by ddiakova          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/15 15:28:17 by ddiakova         ###   ########.fr       */
=======
/*   Updated: 2022/05/17 20:58:12 by jberredj         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
# include "Logger.hpp"
// # include "User.hpp"
# include <iostream>
# include <string>
# include <vector>
# include <map>
// #include "User.hpp"

class User;

class Command
{
public:
	std::string 				_prefix;
	std::string 				_command;
	std::vector<std::string> 	_parameters;
	std::string 				_trailer;
	std::string 				_command_line;
	User*						_user;
	std::vector<User*>* 		_allUsers;

	// Constructors and destructor
								Command(void);
								Command(User* user, std::string command_line,
									std::vector<User *>* users);
								Command(const Command& src);
								~Command(void);

	// Operators
	Command& 					operator=(const Command& rhs);

	// Getters
	std::string					getLine(void) const;
	std::string 				getPrefix(void) const;
	std::string 				getCommand(void) const;
	std::vector<std::string> 	getParameters(void) const;
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
	static std::string	_nickToFind;

	static bool			_nickFinder(User *user);
};

<<<<<<< HEAD
std::ostream &  operator<<(std::ostream & o, Command const & rhs);
void    PASS(Command &command);
void    NICK(Command &command);
=======
// Operators
std::ostream&	operator<<(std::ostream& o, const Command& rhs);
>>>>>>> master

#endif