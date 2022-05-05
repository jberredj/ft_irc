/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:38 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/05 21:33:51 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(std::string command_line) : 
    _prefix(""), _command(""), _trailer(""), _command_line(command_line)
{
	std::string delimiter(" ");
	size_t  	position = 0;
	size_t  	i = 0;

	// 1. Look for prefix
	if (command_line[0] == ':')
	{
		position = command_line.find(delimiter);
		_prefix = command_line.substr(0, position);
		i += position + 1;
	}

	// get command line without prefix
	std::string tmp = command_line.substr(i);

	// get command line without trailer & 4. save trailer if any
	if ((position = command_line.substr(i).find(":")) != std::string::npos)
	{
		tmp = tmp.substr(0, position);
		_trailer = command_line.substr(i + position + 1);
	}

	while ((position = tmp.find(delimiter)) != std::string::npos)
	{
		std::cout << tmp.substr(0, position) << std::endl;
		_parameters.push_back(tmp.substr(0, position));
		tmp.erase(0, position + delimiter.length());
	}
	_parameters.push_back(tmp);
	// 2. get command word
	_command = *(_parameters.begin());
	// put any command character upper case
	for (size_t j = 0; j < _command.length(); ++j)
		_command[j] = toupper(_command[j]);

	// 3. get parameters if any
	_parameters.erase(_parameters.begin());
}

std::ostream &	operator << (std::ostream & o, Command const & rhs)
{
	o << "Line: " << rhs.getLine() << std::endl;
	o << "Prefix : "  << rhs.getPrefix() << std::endl;
	o << "Command : " << rhs.getCommand() << std::endl;
	o << "Parameters : " << std::endl;
	std::vector<std::string>	tmp	= rhs.getParameters();
	for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
		o << "\t" << *it << std::endl;
	o << "Trailer : " << rhs.getTrailer() << std::endl;
	return o;
}