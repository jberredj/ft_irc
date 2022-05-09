/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:39:44 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/09 21:57:04 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

int     main(int ac, char **av)
{
	std::string line1;
	std::string line2;
	(void)ac;
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
	// std::cout << cmd.getCommand() << std::endl;
	// std::cout << cmd1.getCommand() << std::endl;
	user.apply();

	return 0;
}