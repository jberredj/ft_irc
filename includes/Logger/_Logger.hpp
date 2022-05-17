/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _Logger.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:17:45 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 17:21:36 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LOGGER_HPP
# define _LOGGER_HPP
# include "Output.hpp"
# include <ostream>
# include <vector>
# include <iostream>
# include <string>
# include <ctime>  


class Logger {
public:
	// constructors and destructor
	// Constructor is only meant to be used the same way as std::cout would
					Logger(Output::level level);
					~Logger(void);

	// Add outputs functions
	static Output*	addOutput(std::ostream* dest, std::string name,
						Output::level minLevel = Output::INFO,
						Output::level maxLevel = Output::FATAL);
	static Output*	addOutput(std::string filename, 
						Output::level minLevel = Output::INFO,
						Output::level maxLevel = Output::FATAL);
	static Output*	currentTimeAddOutput(std::string filename, 
						Output::level minLevel = Output::INFO,
						Output::level maxLevel = Output::FATAL);

	// Remove output functions
	static bool		removeOutput(Output* toClose);
	static bool		removeOutput(std::string toCloseName);
	static bool		removeOutput(std::ostream* toCloseOstream);
	static void		clearOutputs(void);

	// Operators
	template<typename T>
	const Logger&	operator<<(const T& v) const 
	{
		if (_canLog)
			for (std::vector<Output*>::iterator it = _outputs.begin();
				it != _outputs.end(); it++)
			{
				if (_current_level >= (*it)->getMinLevel()
					&& _current_level <= (*it)->getMaxLevel())
					*(*it) << v;
			}
		else
			std::cerr << v;
		return *this;
	}
	const Logger& operator<<(std::ostream& (*F)(std::ostream&)) const;

private:
	static std::vector<Output*>	_outputs;
	Output::level				_current_level;
	std::tm						_logCreateTime;
	bool						_canLog;
	std::string					_error;
	static const std::string	_print_level[7];
	static const std::string	_color_level[7];
	static std::string			_nameToFind;
	static std::ostream*		_streamToFind;
	static Output				_defaultOutput;

	// constructors
								Logger(void);

	// Logger prefix functions
	void						_logTime(void);
	void						_logLevel(Output::level level);

	// Valid user input functions
	bool						_validLevel(Output::level level);

	// Duplicate check functions
	static Output*				_nameAllreadyInUse(std::string name);
	static Output*				_streamAllreadyInUse(std::ostream* stream);
	static bool					_nameFinder(Output* output);
	static bool					_streamFinder(Output* output);
								
};

#endif