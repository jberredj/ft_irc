/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:03:05 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/09 19:59:12 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void):
_address("Unknown")
{
}

User::User(std::string address):
_address(address)
{
}

User::User(const User &src)
{
	(void)src;
}

User::~User(void)
{
}

User	&User::operator=(const User &rhs)
{

	(void)rhs;
	return *this;
}