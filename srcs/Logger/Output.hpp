/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Output.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:23:24 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/10 23:07:32 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ostream>
#include <string>

#ifndef OUTPUT_HPP
# define OUTPUT_HPP
class Output
{
protected:
	std::ostream		*_dest;
	short				_minLevel;
	short				_maxLevel;
	std::string			_name;
	static const std::string						_print_level[7];
	static const std::string						_color_level[7];

	Output(void);

	Output	&operator=(const Output &rhs);

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
	Output(std::ostream *dest, short minLevel, short maxLevel, std::string name);
	Output(const Output &src);
	virtual ~Output(void);


	short		getMinLevel(void) const;
	short		getMaxLevel(void) const;
	std::string	getName(void) const;
	template<typename T>
	const Output& operator<<(const T& v) const {*_dest << v;return *this;}
	Output const& operator<<(std::ostream& (*F)(std::ostream&)) const;
};
#endif