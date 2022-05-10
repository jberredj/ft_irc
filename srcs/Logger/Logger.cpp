/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:38:23 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/11 01:28:56 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "_Output.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <ctime>  

Logger::Logger(void) {};

bool	Logger::_validLevel(Output::level level)
{
	if (level < Output::TRACE || level > Output::FATAL)
	{
		if (level == Output::INTERNAL)
			_error = "Logger::INTERNAL is reserved to internal logger error";
		else
			_error = "Invalid log level";
		return false;
	}
	return true;
}

void	Logger::_logTime()
{
	std::stringstream	timeToLog;
	timeToLog << std::setfill('0')
			<< "[" 
			<<std::setw(2) << _logCreateTime.tm_year + 1900 << "/"
			<<std::setw(2) << _logCreateTime.tm_mon + 1 << "/"
			<<std::setw(2) << _logCreateTime.tm_mday
			<< " "
			<<std::setw(2) << _logCreateTime.tm_hour << ":"
			<<std::setw(2) << _logCreateTime.tm_min << ":"
			<<std::setw(2) << _logCreateTime.tm_sec
			<< "] - ";
	if (_canLog)
		*this << timeToLog.str();
	else
		std::cerr << timeToLog.str();
}

void	Logger::_logLevel(Output::level level)
{
	if (_canLog)
	{
		for (std::vector<Output>::iterator	it = _outputs.begin(); it != _outputs.end(); it++)
		{
			_Output	*IOutput = reinterpret_cast<_Output *>(&(*it));
			if (&(*IOutput).getDest() == &std::cout)
				*it << _color_level[level];
			*it << _print_level[level];
			if (&(*IOutput).getDest() == &std::cout)
				*it << "\033[0m";
			*it << " - ";
		}
	}
	else
	{
		std::cerr << _color_level[level] << _print_level[level] << "\033[0m";
		std::cerr << " - " << _error;
	}
}

Logger::Logger(Output::level level): _canLog(true)
{
	std::time_t t = std::time(0);
   	_logCreateTime = *std::localtime(&t);
	_canLog = _validLevel(level);
	_logTime();
	if (!_canLog)
	{
		_logLevel(Output::INTERNAL);
		return ;
	}
	_logLevel(level);
}
Logger::~Logger(void)
{
	if(_canLog)
		for (std::vector<Output>::iterator	it = _outputs.begin(); it != _outputs.end(); it++)
			*it << std::endl;
	else
		std::cerr << std::endl;
}

Output	&Logger::addOutput(std::ostream *dest, std::string name, short minLevel, short maxLevel)
{
	Output	newOutput(dest, minLevel, maxLevel, name);
	_outputs.push_back(newOutput);
	return _outputs.back();
}

Logger const& Logger::operator<<(std::ostream& (*F)(std::ostream&)) const
{ 
	for (std::vector<Output>::iterator	it = _outputs.begin(); it != _outputs.end(); it++)
	{
		_Output	*IOutput = reinterpret_cast<_Output *>(&(*it));
		if (IOutput)
			F(IOutput->getDest());
	}
	return *this;
}

std::vector<Output>	Logger::_outputs;

const std::string 						Logger::_print_level[7] = {
	"[INTERNAL]",
	"[TRACE]",
	"[DEBUG]",
	"[INFO]", 
	"[WARNING]", 
	"[ERROR]", 
	"[FATAL]"
};
const std::string 						Logger::_color_level[7] = {
	"\033[1;31m",
	"\033[0;35m",
	"\033[0;94m",
	"",
	"\033[0;33m",
	"\033[0;31m", 
	"\033[1;101m"
};