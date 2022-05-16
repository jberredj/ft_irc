/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _Output.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:30:00 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 22:01:03 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OUTPUT_HPP
# define _OUTPUT_HPP
# include "Logger/Output.hpp"
# include <ostream>

class _Output : public Output
{
public:
	// Getters
	virtual short	getName(void) const = 0;
	std::ostream*	getDest(void) const;
	
	// Setters
	bool			setMinLevel(Output::level minLevel);
	bool			setMaxLevel(Output::level maxLevel);
	void			setName(std::string name);
	void			setOpenedInternally(bool opened);
};

#endif