/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:24:14 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/10 11:31:02 by jberredj         ###   ########.fr       */
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
	static short						_level;
	static std::vector<std::ostream*>	_output;
	static std::map<int, short>			_output_level;
	static const std::string			_print_level[6];
	static const std::string			_color_level[6];
	static bool							_init;

	static void							_log(short level, std::string message);
	
										Logger(void);
										Logger(const Logger &src);
										~Logger(void);
	Logger								&operator=(const Logger &rhs);
public:
	enum level {
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL
	};
	static void							trace(std::string message);
	static void							debug(std::string message);
	static void							info(std::string message);
	static void							warn(std::string message);
	static void							error(std::string message);
	static void							fatal(std::string message);
	static void							init(short level);
	static void							destroy(void);
	static void							create_log_file(std::string filename, short level);
};

#endif