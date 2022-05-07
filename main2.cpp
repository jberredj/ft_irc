/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:39:44 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/07 17:51:01 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

int     main(int ac, char **av)
{
	std::string line1;
	std::string line2;

	if (ac < 3)
		return 1;
	line1 = std::string(av[1]);
	line2 = std::string(av[2]);
	
	User		user;
	Command     cmd(&user, line1);
	Command     cmd1(&user, line2);
	
	std::cout << user << std::endl;
	std::cout << cmd << std::endl;
	std::cout << cmd1 << std::endl;
	user.addToqueue(cmd);
	user.addToqueue(cmd1);
	user.apply();

	return 0;
}