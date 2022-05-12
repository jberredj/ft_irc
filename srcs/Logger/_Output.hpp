/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _Output.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:30:00 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/12 23:57:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OUTPUT_HPP
# define _OUTPUT_HPP
# include "Logger/Output.hpp"
class _Output : Output
{
public:
	virtual short	getName(void) const = 0;
	std::ostream	&getDest(void) const;
	bool			setMinLevel(Output::level minLevel);
	bool			setMaxLevel(Output::level maxLevel);
	void			setName(std::string name);
	void			setOpenedInternally(bool opened);
};

#endif