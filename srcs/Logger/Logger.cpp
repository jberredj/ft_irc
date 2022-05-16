/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:38:23 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 22:01:39 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/Nullptr_t.hpp"
#include "Logger/_Logger.hpp"
#include "_Output.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <exception>

/* ************************************************************************** */
/*                                 Public                                     */
/* ************************************************************************** */

// constructors and destructor
Logger::Logger(Output::level level):
	_canLog(true)
{
	_current_level = level;
	if (!_validLevel(level))
		return ;
	std::time_t t = std::time(0);
   	_logCreateTime = *std::localtime(&t);
	_logTime();
	_logLevel(level);
}

Logger::~Logger(void)
{
	if(_canLog)
	{
		for (std::vector<Output *>::iterator it = _outputs.begin();
			it != _outputs.end(); it++
		)
			if (_current_level >= (*it)->getMinLevel()
				&& _current_level <= (*it)->getMaxLevel())
				*(*it) << std::endl;
	}
	else
		std::cerr << std::endl;
}

// Add outputs functions
Output* Logger::addOutput(std::ostream* dest, std::string name,
	Output::level minLevel, Output::level maxLevel)
{
	Output *find = _streamAllreadyInUse(dest);
	if (find)
	{
		Logger() << "Requested stream is allready in use";
		return find;
	}
	find = _nameAllreadyInUse(name);
	if (find)
	{
		Logger() << "Name \"" << name << "\" is allready in use";
		return find;
	}
	Output	*newOutput = new Output(dest, name, minLevel, maxLevel);
	_outputs.push_back(newOutput);
	return newOutput;
}

Output	*Logger::addOutput(std::string filename, Output::level minLevel,
	Output::level maxLevel
)
{
	Output *find = _nameAllreadyInUse(filename);
	if (find)
	{
		Logger() << "Name \"" << filename << "\" is allready in use";
		return find;
	}
	try
	{
		Output	*newOutput = new Output(filename, minLevel, maxLevel);
		_outputs.push_back(newOutput);
		return newOutput;
	}
	catch(const std::exception& e)
		{Logger() << e.what();}
	return ft::null_ptr;
}

Output *Logger::currentTimeAddOutput(std::string filename,
	Output::level minLevel, Output::level maxLevel
)
{
	std::stringstream	timecode;
	std::time_t t = std::time(0);
   	std::tm now = *std::localtime(&t);

	timecode << std::setfill('0')
		<< std::setw(2) << now.tm_year + 1900 << "_"
		<<std::setw(2) << now.tm_mon + 1 << "_"
		<<std::setw(2) << now.tm_mday << "_"
		<<std::setw(2) << now.tm_hour << "_"
		<<std::setw(2) << now.tm_min << "_"
		<<std::setw(2) << now.tm_sec << "_";
	timecode << filename;
	return addOutput(timecode.str(), minLevel, maxLevel);
}

// Remove output functions
bool						Logger::removeOutput(Output *toClose)
{
	std::vector<Output *>::iterator	it = std::find(_outputs.begin(),
		_outputs.end(), toClose);
	if (it == _outputs.end())
	{
		Logger() << "Cannot remove output because it's not tracked in Logger";
		return false;
	}
	_outputs.erase(it);
	delete toClose;
	return true;
}

bool						Logger::removeOutput(std::string toCloseName)
{
	Output *toClose = _nameAllreadyInUse(toCloseName);
	if (!toClose)
	{
		Logger() << "Cannot remove output \"" << toCloseName 
			<< "\" because it's not tracked in Logger";
		return false;
	}
	_outputs.erase(std::find(_outputs.begin(), _outputs.end(), toClose));
	delete toClose;
	return true;
}

bool						Logger::removeOutput(std::ostream *toCloseOstream)
{
	Output *toClose = _streamAllreadyInUse(toCloseOstream);
	if (!toClose)
	{
		Logger() << "Cannot remove output by this ostream because"
			<< " it's not tracked in Logger";
		return false;
	}
	_outputs.erase(std::find(_outputs.begin(), _outputs.end(), toClose));
	delete toClose;
	return true;
}

void						Logger::clearOutputs(void)
{
	for (std::vector<Output *>::iterator	it = _outputs.begin();
		it != _outputs.end(); it++
	)
		delete (*it);
	_outputs.clear();
}

// Operators
Logger const& Logger::operator<<(std::ostream& (*F)(std::ostream&)) const
{ 
	for (std::vector<Output *>::iterator it = _outputs.begin();
		it != _outputs.end(); it++)
	{
		_Output	*IOutput = static_cast<_Output *>((*it));
		if (IOutput && (_current_level >= (*it)->getMinLevel() 
			&& _current_level <= (*it)->getMaxLevel()))
			F(reinterpret_cast<std::ostream &>(*IOutput->getDest()));
	}
	return *this;
}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

// Static variable initialisation
std::vector<Output*>	Logger::_outputs;
Output					Logger::_defaultOutput;
std::string				Logger::_nameToFind;
std::ostream*			Logger::_streamToFind = ft::null_ptr; 
const std::string		Logger::_print_level[7] = {"[INTERNAL]", "[TRACE]",
													"[DEBUG]", "[INFO]",
													"[WARNING]", "[ERROR]", 
													"[FATAL]"};
const std::string		Logger::_color_level[7] = {"\033[1;31m", "\033[0;35m",
													"\033[0;94m", "",
													"\033[0;33m", "\033[0;31m", 
													"\033[1;101m"};

// Constructor
Logger::Logger(void):
	_canLog(false)
{
	std::time_t t = std::time(0);

	_current_level = Output::INTERNAL;
   	_logCreateTime = *std::localtime(&t);
	_logTime();
	_logLevel(Output::INTERNAL);
}

// Logger prefix functions
void	Logger::_logTime()
{
	std::stringstream	timeToLog;

	timeToLog << std::setfill('0')
		<< "[" 
		<< std::setw(2) << _logCreateTime.tm_year + 1900 << "/"
		<< std::setw(2) << _logCreateTime.tm_mon + 1 << "/"
		<< std::setw(2) << _logCreateTime.tm_mday << " "
		<< std::setw(2) << _logCreateTime.tm_hour << ":"
		<< std::setw(2) << _logCreateTime.tm_min << ":"
		<< std::setw(2) << _logCreateTime.tm_sec << "] - ";
	if (_canLog)
		*this << timeToLog.str();
	else
		std::cerr << timeToLog.str();
}

void	Logger::_logLevel(Output::level level)
{
	if (_canLog)
	{
		for (std::vector<Output*>::iterator it = _outputs.begin();
			it != _outputs.end(); it++)
		{
			if (_current_level >= (*it)->getMinLevel() 
				&& _current_level <= (*it)->getMaxLevel())
			{
				_Output* IOutput = static_cast<_Output *>((*it));
				if ((*IOutput).getDest() == &std::cout)
					*(*it) << _color_level[level];
				*(*it) << _print_level[level];
				if ((*IOutput).getDest() == &std::cout)
					*(*it) << "\033[0m";
				*(*it) << " - ";
			}
		}
	}
	else
	{
		std::cerr << _color_level[level] << _print_level[level] << "\033[0m";
		std::cerr << " - " << _error;
	}
}

// Valid user input functions
bool	Logger::_validLevel(Output::level level)
{
	if (level < Output::TRACE || level > Output::FATAL)
	{
		if (level == Output::INTERNAL)
			Logger() << "Logger::INTERNAL is reserved to internal logger error";
		else
			Logger() << "Invalid log level";
		return false;
	}
	return true;
}

// Duplicate check functions
bool	Logger::_nameFinder(Output* output)
{
	if (output->getName() == _nameToFind)
		return true;
	return false;
}

Output*	 Logger::_nameAllreadyInUse(std::string name)
{
	_nameToFind = name;
	std::vector<Output*>::iterator	it = std::find_if(_outputs.begin(),
		_outputs.end(), _nameFinder);
	if (it != _outputs.end())
		return *it;
	return ft::null_ptr;
}

bool	Logger::_streamFinder(Output* output)
{
	_Output*	IOutput = static_cast<_Output*>(output);
	if ((IOutput->getDest()) == _streamToFind)
		return true;
	return false;
}

Output*	Logger::_streamAllreadyInUse(std::ostream* stream)
{
	_streamToFind = stream;
	std::vector<Output*>::iterator	it = std::find_if(_outputs.begin(),
		_outputs.end(), _streamFinder);
	_streamToFind = ft::null_ptr;
	if (it != _outputs.end())
		return *it;
	return ft::null_ptr;
}