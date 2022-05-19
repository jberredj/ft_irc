/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeHelper.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:52:28 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/18 14:09:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
#include "modeHelper.hpp"

int	hasMode(std::string toCheck, std::string modeStr)
{
	int	found = 0;
	for(std::string::iterator it = toCheck.begin(); it != toCheck.end(); it++)
		if (modeStr.find(*it) != modeStr.npos)
			found++;
	return found;
}

bool	addMode(std::string toAdd, std::string &modeStr)
{
	for(std::string::iterator it = toAdd.begin(); it != toAdd.end(); it++)
		if (!hasMode(*it, modeStr))
			modeStr +=
}