/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nullptr_t.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:24:11 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/14 12:45:44 by ddiakova         ###   ########.fr       */
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
		(void)rhs; 
		return *this;
	}
}