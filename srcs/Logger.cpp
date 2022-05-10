/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:27:30 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/10 18:08:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "types/Nullptr_t.hpp"
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <filesystem>

/* Because this class contain only static function, all of these are private*/
/**/Logger::Logger(void)
/**/{
/**/}
/**/
/**/Logger::Logger(const Logger &src)
/**/{
/**/	(void)src;
/**/}
/**/
/**/Logger::~Logger(void)
/**/{
/**/	destroy();
/**/}
/**/
/**/Logger	&Logger::operator=(const Logger &rhs)
/**/{
/**/
/**/	(void)rhs;
/**/	return *this;
/**/}
/****************************************************************************/

std::tm	Logger::_logTime(void)
{
	std::time_t t = std::time(0);
   	std::tm now_utc = *std::localtime(&t);
	return now_utc;
}

bool	Logger::_validLevel(short level)
{
	if (level < Logger::TRACE || level > Logger::FATAL)
	{
		if (level == Logger::INTERNAL)
			_log(Logger::INTERNAL, "Logger::INTERNAL is reserved to internal logger error", &std::cout, _logTime());
		else
			_log(Logger::INTERNAL, "Invalid log error", &std::cout, _logTime());
		return false;
	}
	return true;
}

void	Logger::_log(short level, std::string message, std::ostream *output, std::tm now_utc)
{
	if ((_output_level[output] <= level && level >= _min_output_level[output]) || level == Logger::INTERNAL)
	{
		*output << std::setfill('0')
			<< "[" 
			<<std::setw(2) << now_utc.tm_year + 1900 << "/"
			<<std::setw(2) << now_utc.tm_mon + 1 << "/"
			<<std::setw(2) << now_utc.tm_mday
			<< " "
			<<std::setw(2) << now_utc.tm_hour << ":"
			<<std::setw(2) << now_utc.tm_min << ":"
			<<std::setw(2) << now_utc.tm_sec
			<< "] - ";
		if (output == &std::cout)
			*output << _color_level[level];
		*output << _print_level[level];
		if (output == &std::cout)
			*output << "\033[0m";
		*output << " - " << message << std::endl;
	}
}

void	Logger::_logToAll(short level, std::string message)
{
	for (size_t i = 0; i < _output.size(); i++)
	{
		_log(level, message, _output[i], _logTime());
	}
}

void	Logger::trace(std::string message)
{
	if (_init)
		Logger::_logToAll(TRACE, message);
}

void	Logger::debug(std::string message)
{
	if (_init)
		Logger::_logToAll(DEBUG, message);
}

void	Logger::info(std::string message)
{
	if (_init)
		Logger::_logToAll(INFO, message);
}

void	Logger::warn(std::string message)
{
	if (_init)
		Logger::_logToAll(WARN, message);
}

void	Logger::error(std::string message)
{
	if (_init)
		Logger::_logToAll(ERROR, message);
}

void	Logger::fatal(std::string message)
{
	if (_init)
		Logger::_logToAll(FATAL, message);
}

void	Logger::destroy()
{
	std::ofstream	*to_close = ft::null_ptr;
	for (size_t i = 0; i < _output.size(); i++)
	{
		to_close = dynamic_cast<std::ofstream *>(_output[i]);
		if (to_close)
		{
			to_close->close();
			_output_level.erase(_output[i]);
			_min_output_level.erase(_output[i]);
			std::map<std::string, std::ostream *>::iterator file_found = _open_file_name.begin();
			while(file_found != _open_file_name.end() && file_found->second != _output[i])
			{
				file_found++;
			}
			if (file_found != _open_file_name.end())
				_open_file_name.erase(file_found);
			// _output.erase(to_close);
			delete to_close;
		}
	}
}

std::ostream	*Logger::_createLogFile(std::string filename, short level, short minLevel)
{
	if (!_validLevel(level) || !_validLevel(minLevel))
		return ft::null_ptr;
	std::ofstream	*file;
	try
	{
		std::ostream	*found = _open_file_name.at(filename);
		_log(Logger::INTERNAL, "File \"" + filename + "\" is allready oppened in logger", &std::cout, _logTime());
		return found;
	}
	catch(const std::exception& e) {(void)e;};
	file = new std::ofstream;
	file->open(filename.c_str(), std::ofstream::app | std::ofstream::out);
	if (!file->is_open())
	{
		_log(Logger::INTERNAL, "Unable to open file: " + filename, &std::cout, _logTime());
		delete file;
		return ft::null_ptr;
	}
	_output.push_back(file);
	_output_level.insert(std::make_pair(file, level));
	_open_file_name.insert(std::make_pair(filename, file));
	return file;
}

std::ostream	*Logger::createLogFile(std::string filename, short level, short minLevel)
{
	std::ostream *ptr;
	ptr = _createLogFile(filename, level, minLevel);
	if (ptr)
		return ptr;
	_log(Logger::INTERNAL, "Cannot create logger to file: " + filename, &std::cout, _logTime());
	return ft::null_ptr;
}

std::ostream	*Logger::logFileNow(std::string filename, short level, short minLevel)
{
	std::stringstream	new_name;
	std::tm				now_utc;
	std::ostream		*ptr;
	now_utc = _logTime();

	new_name << std::setfill('0') <<std::setw(2) << now_utc.tm_year + 1900 << "_"
			<<std::setw(2) << now_utc.tm_mon + 1 << "_"
			<<std::setw(2) << now_utc.tm_mday << "_"
			<<std::setw(2) << now_utc.tm_hour << "_"
			<<std::setw(2) << now_utc.tm_min << "_"
			<<std::setw(2) << now_utc.tm_sec << "_";
	new_name << filename;
	ptr = _createLogFile(new_name.str(), level, minLevel);
	if (ptr)
		return ptr;
	_log(Logger::INTERNAL, "Cannot create logger to file: " + new_name.str(), &std::cout, _logTime());
	return ft::null_ptr;
}

std::ostream	*Logger::logToCout(short level, short minLevel)
{
	if (level > minLevel)
	{
		_log(Logger::INTERNAL, "level need to be higher than minLevel", &std::cout, _logTime());
		return ft::null_ptr;
	}
	if (!_validLevel(level) || !_validLevel(minLevel))
		return ft::null_ptr;
	if(find(_output.begin(), _output.end(), &std::cout) != _output.end())
	{
		_log(Logger::INTERNAL, "std::cout is already registered in logger", &std::cout, _logTime());
		return ft::null_ptr;
	}
	Logger::_output_level.insert(std::make_pair(&std::cout, level));
	Logger::_output.push_back(&std::cout);
	return &std::cout;
}

bool	Logger::closeLogger(std::string filename)
{
	std::ostream *ptr;
	try
	{
		ptr = _open_file_name.at(filename);
		std::vector<std::ostream *>::iterator	output;
		output = find(_output.begin(), _output.end(), ptr);
		dynamic_cast<std::ofstream *>(*output)->close();
		_output_level.erase(*output);
		_min_output_level.erase(*output);
		_open_file_name.erase(filename);
		_output.erase(output);
		delete dynamic_cast<std::ofstream *>(*output);
	}
	catch(const std::exception& e)
	{
		(void)e;
		_log(Logger::INTERNAL, filename + " is not a registered logger file output", &std::cout, _logTime());
		return false;
	}
	return true;
}

bool	Logger::closeLogger(std::ostream *ptr)
{
	std::vector<std::ostream *>::iterator	output = find(_output.begin(), _output.end(), ptr);
	if (output != _output.end())
	{
		dynamic_cast<std::ofstream *>(ptr)->close();
		_output_level.erase(ptr);
		_min_output_level.erase(ptr);
		std::map<std::string, std::ostream *>::iterator file_found = _open_file_name.begin();
		while(file_found != _open_file_name.end() && file_found->second != ptr)
			file_found++;
		if (file_found != _open_file_name.end())
			_open_file_name.erase(file_found);
		_output.erase(output);
		delete ptr;
		return true;
	}
	else
	{
		_log(Logger::INTERNAL, "No logger registered using this ostream", &std::cout, _logTime());
	}
	return false;
}

std::vector<std::ostream *>				Logger::_output;
std::map<std::ostream *, short>			Logger::_output_level;
std::map<std::ostream *, short>			Logger::_min_output_level;
std::map<std::string, std::ostream *>	Logger::_open_file_name;
short 									Logger::_level = Logger::INFO;
bool									Logger::_init = true;
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
