/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:33 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/05 15:07:19 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
#include <iostream>
#include <string>
#include <vector>
#include "User.hpp"

class User;

class Command
{
	private:
		std::string 				_prefix;
		std::string 				_command;
		std::vector<std::string> 	_parameters;
		std::string 				_trailer;
		std::string 				_command_line;

	public:
		Command() {}
		Command(std::string command_line);
		Command(Command const & src): _command_line(src._command_line) {}
		Command & operator = (Command const & rhs)
		{
			_command_line = rhs._command_line;
			return (*this);
		}
		~Command() {}
		std::string					getLine() const {return _command_line; }
		std::string 				getPrefix() const {return _prefix; }
		std::string 				getCommand() const { return _command; }
		std::vector<std::string> 	getParameters() const { return _parameters; }
		std::string 				getTrailer() const{ return _trailer; }
		void						print_prm(std::vector<std::string> _parameters );

};

std::ostream &  operator<<(std::ostream & o, Command const & rhs);

#endif