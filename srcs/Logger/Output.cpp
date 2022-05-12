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
#include <iostream>
#include "Logger/Output.hpp"
#include "_Output.hpp"
#include "types/Nullptr_t.hpp"

std::map<std::string, int>*	Output::_nbrCopy = ft::null_ptr;

					Output::Output(void): 
					_dest(&std::cerr), _minLevel(Output::NOUTPUT), _maxLevel(Output::NOUTPUT),
					_name("DEFAULT"), _openedInternally(false) {}

					Output::Output(std::ostream *dest, std::string name,
						Output::level minLevel, Output::level maxLevel
					) : _dest(dest), _minLevel(minLevel), _maxLevel(maxLevel),
						_name(name), _openedInternally(false)
{
	if (!Output::_nbrCopy)
		Output::_nbrCopy = new std::map<std::string, int>;
	Output::_nbrCopy->insert(std::make_pair(name, 1));
}

					Output::Output(std::string name, Output::level minLevel,
						Output::level maxLevel
					) : _minLevel(minLevel), _maxLevel(maxLevel), _name(name),
						_openedInternally(false)
{
	std::ofstream *dest = new std::ofstream;
	dest->open(name.c_str(), std::fstream::app | std::fstream::out);
	if (!dest->is_open())
		throw(std::runtime_error("Unable to open file: " + name));
	if (!Output::_nbrCopy)
		Output::_nbrCopy = new std::map<std::string, int>;
	Output::_nbrCopy->insert(std::make_pair(name, 1));
	_openedInternally = true;
	_dest = dest;
}

					Output::Output(const Output &src): 
						_dest(src._dest), _minLevel(src._minLevel),
						_maxLevel(src._maxLevel),
						_name(src._name), 
						_openedInternally(src._openedInternally)
{
	if (_name == "DEFAULT")
		return ;
	(*Output::_nbrCopy)[_name]++;
}

					Output::~Output(void)
{
	if (_name == "DEFAULT")
		{return ;}
	(*Output::_nbrCopy)[_name]--;
	if (_openedInternally)
	{
		if ((*Output::_nbrCopy)[_name] == 0)
		{
			reinterpret_cast<std::ofstream *>(this->_dest)->close();
			delete this->_dest;
		}
	}
	if ((*Output::_nbrCopy)[_name] == 0)
	{
		Output::_nbrCopy->erase(_name);
	}
	if(!Output::_nbrCopy->size())
	{
		delete Output::_nbrCopy;
		Output::_nbrCopy = ft::null_ptr;
	}
}

Output				&Output::operator=(const Output &rhs)
{
	if (this != &rhs)
	{
		if (_name != "DEFAULT")
			(*Output::_nbrCopy)[_name]++;
		this->_dest = rhs._dest;
		this->_openedInternally = rhs._openedInternally;
		this->_minLevel = rhs._maxLevel;
		this->_maxLevel = rhs._maxLevel;
		this->_name = rhs._name;
	}
	return *this;
}

const Output 		&Output::operator<<(
						std::ostream& (*F)(std::ostream&)
					) const
{
	F(dynamic_cast<std::ostream &>(*_dest));
	return *this;
}

Output::level		Output::getMinLevel(void) const {return _minLevel;}
Output::level		Output::getMaxLevel(void) const {return _maxLevel;}
std::string			Output::getName(void) const {return _name;}

bool				_Output::setMinLevel(Output::level minLevel)
{
	if ((minLevel >= TRACE || minLevel <= FATAL) && minLevel >= _maxLevel)
	{
		_minLevel = minLevel;
		return true;
	}
	return false;
}

bool				_Output::setMaxLevel(Output::level maxLevel)
{
	if ((maxLevel >= TRACE || maxLevel <= FATAL) && maxLevel <= _minLevel)
	{
		_maxLevel = maxLevel;
		return true;
	}
	return false;
}

void				_Output::setName(std::string name)
{
	Output::_nbrCopy->insert(std::make_pair(name, (*Output::_nbrCopy)[_name]));
	Output::_nbrCopy->erase(_name);
	_name = name;
}

bool				operator==(const Output& lhs, const Output& rhs)
{
	if (lhs.getName() != rhs.getName() ||
		lhs.getMaxLevel() != rhs.getMaxLevel()
		|| lhs.getMinLevel() != rhs.getMinLevel())
		return false;
	return true;
}

std::ostream		&operator<<(std::ostream &o, const Output& src)
{
	o << "Output \"" << src.getName() << "\" with log level of "
		<< src.getMinLevel() << ":" << src.getMaxLevel();
	return o;
}

bool 				operator!=(const Output& lhs, const Output& rhs) 
{
	return !(lhs == rhs);
}

void				_Output::setOpenedInternally(bool opened)
{
	_openedInternally = opened;
}
std::ostream		&_Output::getDest(void) const 
{
	return reinterpret_cast<std::ostream &>(*_dest);
}