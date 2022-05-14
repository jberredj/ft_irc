/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:33 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/14 23:37:49 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
# include "Logger.hpp"
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

		User *_user;

	public:
		Command() {}
		Command(User *user, std::string command_line);
		Command(Command const & src)
		: 	_prefix(src._prefix),
			_command(src._command),
			_parameters(src._parameters),
			_trailer(src._trailer),
			_command_line(src._command_line),
			_user(src._user) {
				Logger(Output::TRACE) << "Command copy constructor called ";
			}
		Command & operator = (Command const & rhs)
		{
			Logger(Output::TRACE) << "Command assignement operator called ";
			_command_line = rhs._command_line;
			_prefix = rhs._prefix;
			_command = rhs._command;
			_parameters = rhs._parameters;
			_user = rhs._user;
			_trailer = rhs._trailer;
			return (*this);
		}
		~Command() {}
		std::string					getLine() const {return _command_line; }
		std::string 				getPrefix() const {return _prefix; }
		std::string 				getCommand() const { return _command; }
		std::vector<std::string> 	getParameters() const { return _parameters; }
		std::string 				getTrailer() const{ return _trailer; }
		User 						&getUser() const {return *_user;}
		
		void						print_prm(std::vector<std::string> _parameters );

};

std::ostream &  operator<<(std::ostream & o, Command const & rhs);
void    PASS(Command &command);

#endif