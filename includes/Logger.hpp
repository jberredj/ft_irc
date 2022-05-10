/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:24:14 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/10 17:17:14 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP
# include <string>
# include <vector>
# include <iostream>
# include <iomanip>
# include <ostream>
# include <ctime>  
# include <vector>
# include <map>

class Logger
{

private:
	static short									_level;
	static std::vector<std::ostream*>				_output;
	static std::map<std::string, std::ostream *>	_open_file_name;
	static std::map<std::ostream *, short>			_output_level;
	static std::map<std::ostream *, short>			_min_output_level;
	static const std::string						_print_level[7];
	static const std::string						_color_level[7];
	static bool										_init;

	static std::tm									_logTime(void);
	static bool										_validLevel(short level);
	static void										_logToAll(short level, std::string message);
	static void										_log(short level, std::string message, std::ostream *output, std::tm now_utc);
	static std::ostream								*_createLogFile(std::string filename, short level, short minLevel);
	
													Logger(void);
													Logger(const Logger &src);
													~Logger(void);
	Logger											&operator=(const Logger &rhs);
public:
	enum level {
		INTERNAL,
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL
	};
	static void										trace(std::string message);
	static void										debug(std::string message);
	static void										info(std::string message);
	static void										warn(std::string message);
	static void										error(std::string message);
	static void										fatal(std::string message);
	static std::ostream								*logToCout(short level, short minLevel = Logger::FATAL);
	static void										destroy(void);
	static std::ostream								*createLogFile(std::string filename, short level, short minLevel = Logger::FATAL);
	static std::ostream								*logFileNow(std::string filename, short level, short minLevel = Logger::FATAL);
	static bool										closeLogger(std::string filename);
	static bool										closeLogger(std::ostream *ptr);
};

#endif