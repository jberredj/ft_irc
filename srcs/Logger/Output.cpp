/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Output.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:22:13 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/10 23:06:25 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ostream>
#include <fstream>
#include <string>
#include "Output.hpp"
#include "_Output.hpp"

Output::Output(void) {}

Output::Output(std::ostream *dest, short minLevel, short maxLevel, std::string name):
_dest(dest), _minLevel(minLevel), _maxLevel(maxLevel), _name(name) {}

Output::Output(const Output &src):
_dest(src._dest), _minLevel(src._minLevel), _maxLevel(src._maxLevel), _name(src._name) {}

Output::~Output(void)
{
	std::ofstream	*isFile = dynamic_cast<std::ofstream *>(this->_dest);
	if (isFile)
		isFile->close();
}

Output	&Output::operator=(const Output &rhs)
{
	if (this != &rhs)
	{
		std::ofstream	*isFile = dynamic_cast<std::ofstream *>(this->_dest);
		if (isFile)
			isFile->close();
		this->_dest = rhs._dest;
		this->_minLevel = rhs._maxLevel;
		this->_maxLevel = rhs._maxLevel;
		this->_name = rhs._name;
	}
	return *this;
}

Output const& Output::operator<<(std::ostream& (*F)(std::ostream&)) const
{
	F(dynamic_cast<std::ostream &>(*_dest));
	return *this;
}

short		Output::getMinLevel(void) const {return _minLevel;}
short		Output::getMaxLevel(void) const {return _maxLevel;}
std::string	Output::getName(void) const {return _name;}

bool		_Output::setMinLevel(short minLevel)
{
	if ((minLevel >= TRACE || minLevel <= FATAL) && minLevel >= _maxLevel);
	{
		_minLevel = minLevel;
		return true;
	}
	return false;
}

bool		_Output::setMaxLevel(short maxLevel)
{
	if ((maxLevel >= TRACE || maxLevel <= FATAL) && maxLevel <= _minLevel);
	{
		_maxLevel = maxLevel;
		return true;
	}
	return false;
}

void		_Output::setName(std::string name)
{
	_name = name;
}

std::ostream	&_Output::getDest(void) const {return reinterpret_cast<std::ostream &>(*_dest);}