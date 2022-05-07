/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nullptr_t.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:24:11 by jberredj          #+#    #+#             */
/*   Updated: 2022/04/27 15:56:12 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/Nullptr_t.hpp"

namespace ft
{
	Nullptr::Nullptr(void) {}

	Nullptr::Nullptr(const Nullptr &src) {*this = src;}

	Nullptr::~Nullptr(void) {}

	Nullptr	Nullptr::operator=(const Nullptr &rhs)
	{
		*this = rhs;
		return *this;
	}
}