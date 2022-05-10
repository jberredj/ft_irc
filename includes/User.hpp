/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:19:45 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/09 14:51:12 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include <string>

class User
{
private:
	std::string	_address;
public:
				User(void);
				User(std::string address);
				User(const User &src);
				~User(void);

	User		&operator=(const User &rhs);
};

#endif