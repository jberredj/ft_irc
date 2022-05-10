/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:17:45 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/11 01:18:04 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ostream>
#include <vector>
#include "_Output.hpp"
#include <string>
#include <ctime>  


class Logger {
private:
	static std::vector<Output>	_outputs;
	std::tm						_logCreateTime;
	bool						_canLog;
	std::string					_error;
	static const std::string						_print_level[7];
	static const std::string						_color_level[7];

	void											_logTime(void);
	void											_logLevel(Output::level level);
	bool										_validLevel(Output::level level);
	Logger(void);

public:
	static Output	&addOutput(std::ostream *dest, std::string name, short minLevel = Output::INFO, short maxLevel = Output::FATAL);
	Logger(Output::level level);
	~Logger(void);
	template<typename T>
	const Logger& operator<<(const T& v) const {
		for (std::vector<Output>::iterator	it = _outputs.begin(); it != _outputs.end(); it++)
			*it << v;
		return *this;
	}
	Logger const& operator<<(std::ostream& (*F)(std::ostream&)) const;
};
