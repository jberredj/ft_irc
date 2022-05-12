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
#include <map>

#ifndef OUTPUT_HPP
# define OUTPUT_HPP
class Output
{
public:
	enum level {
		INTERNAL,
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL,
		NOUTPUT
	};	
protected:
	static std::map<std::string, int>* _nbrCopy;
	std::ostream				*_dest;
	Output::level				_minLevel;
	Output::level				_maxLevel;
	std::string					_name;
	bool						_openedInternally;

public:
								Output(void);
								Output(std::ostream *dest, std::string name, 
									Output::level minLevel = DEBUG, 
									Output::level maxLevel = FATAL
								);
								Output(std::string name,
									Output::level minLevel = DEBUG,
									Output::level maxLevel = FATAL
								);
								Output(const Output &src);
	virtual						~Output(void);

	Output::level				getMinLevel(void) const;
	Output::level				getMaxLevel(void) const;
	std::string					getName(void) const;
	template<typename T>
	const Output& 				operator<<(const T& v) const 
	{
		*_dest << v;
		return *this;
	}
	Output const& 				operator<<(
									std::ostream& (*F)(std::ostream&)
								) const;
	Output						&operator=(const Output &rhs);
};

std::ostream					&operator<<(std::ostream &o, const Output& src);

bool 							operator==(const Output& lhs, const Output& rhs);
bool							operator!=(const Output& lhs, const Output& rhs);

#endif