/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nullptr_t.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:24:11 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 18:50:37 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/Nullptr_t.hpp"

namespace ft
{
/* ************************************************************************** */
/*                                  Public                                    */
/* ************************************************************************** */

// Constructors dans destructor
	Nullptr::Nullptr(void) {}

	Nullptr::Nullptr(const Nullptr &src) {*this = src;}

	Nullptr::~Nullptr(void) {}

// Operators
	Nullptr	Nullptr::operator=(const Nullptr &rhs) 
	{
		(void)rhs; 
		return *this;
	}

/* ************************************************************************** */
/*                                 Private                                    */
/* ************************************************************************** */

// Operators
	void	Nullptr::operator&() const {};
}