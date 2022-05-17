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

#ifndef OUTPUT_HPP
# define OUTPUT_HPP
# include <ostream>
# include <string>
# include <map>


class Output
{
public:
	enum			level {INTERNAL, TRACE, DEBUG, INFO, WARN, ERROR, FATAL,
						NOUTPUT};

	// Constructors and destructor
					Output(void);
					Output(std::ostream* dest, std::string name, 
						Output::level minLevel = DEBUG, 
						Output::level maxLevel = FATAL);
					Output(std::string name,
						Output::level minLevel = DEBUG,
						Output::level maxLevel = FATAL);
					Output(const Output& src);
					~Output(void);

	// Getters
	Output::level	getMinLevel(void) const;
	Output::level	getMaxLevel(void) const;
	std::string		getName(void) const;

	// Operators
	template<typename T>
	const Output&	operator<<(const T& v) const 
	{
		*_dest << v;
		return *this;
	}
	const Output&	operator<<(std::ostream& (*F)(std::ostream&)) const;
	Output&			operator=(const Output& rhs);

protected:
	std::ostream*						_dest;
	Output::level						_minLevel;
	Output::level						_maxLevel;
	std::string							_name;
	bool								_openedInternally;
	static std::map<std::string, int>*	_nbrCopy;
};

// Operators
std::ostream&	operator<<(std::ostream& o, const Output& src);
bool			operator==(const Output& lhs, const Output& rhs);
bool			operator!=(const Output& lhs, const Output& rhs);

#endif