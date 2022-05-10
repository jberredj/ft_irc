/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:27:30 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/10 09:10:12 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "types/Nullptr_t.hpp"
#include <fstream>

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

void	Logger::_log(short level, std::string message)
{
	std::time_t t = std::time(0);   // get time now
    std::tm now_utc = *std::localtime(&t);
	for (size_t i = 0; i < _output.size(); i++)
	{
		if (_output_level[i] <= level)
		{
			*_output[i] << std::setfill('0')
				<< "[" 
				<<std::setw(2) << now_utc.tm_year + 1900 << "/"
				<<std::setw(2) << now_utc.tm_mon + 1 << "/"
				<<std::setw(2) << now_utc.tm_mday
				<< " "
				<<std::setw(2) << now_utc.tm_hour << ":"
				<<std::setw(2) << now_utc.tm_min << ":"
				<<std::setw(2) << now_utc.tm_sec
				<< "] - ";
			if (_output[i] == &std::cout)
				*_output[i] << _color_level[level];
			*_output[i] << _print_level[level];
			if (_output[i] == &std::cout)
				*_output[i] << "\033[0m";
			*_output[i] << " - " << message << std::endl;
		}
	}
}

void	Logger::debug(std::string message)
{
	if (_init)
		Logger::_log(DEBUG, message);
}

void	Logger::info(std::string message)
{
	if (_init)
		Logger::_log(INFO, message);
}

void	Logger::warn(std::string message)
{
	if (_init)
		Logger::_log(WARN, message);
}

void	Logger::error(std::string message)
{
	if (_init)
		Logger::_log(ERROR, message);
}

void	Logger::fatal(std::string message)
{
	if (_init)
		Logger::_log(FATAL, message);
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
			_output_level.erase(i);
			delete to_close;
			std::cout << "close" << std::endl;
		}
	}
}

void	Logger::create_log_file(std::string filename, short level)
{
	std::ofstream	*file;
	file = new std::ofstream;

	file->open(filename.c_str(), std::ofstream::app | std::ofstream::out);
	_output.push_back(file);
	_output_level.insert(std::make_pair(_output.size(), level));
}

void	Logger::init(short level)
{
	Logger::_output.push_back(&std::cout);
	Logger::_output_level.insert(std::make_pair(0, level));

	Logger::_init = true;
}

std::vector<std::ostream *>	Logger::_output;
std::map<int, short> Logger::_output_level;
short Logger::_level = Logger::INFO;
bool Logger::_init = false;
const std::string Logger::_print_level[5] = {"[DEBUG]", "[INFO]", "[WARNING]", "[ERROR]", "[FATAL]"};
const std::string Logger::_color_level[5] = {"\033[0;94m", "", "\033[0;33m", "\033[0;31m", "\033[1;101m"};
