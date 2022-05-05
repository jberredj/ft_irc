/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:39:44 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/05 20:32:51 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "User.hpp"

int     main(int ac, char **av)
{
	std::string line;
	line = std::string(av[1]);
	(void)ac;

	Command     cmd(line);
	User		user;
	std::cout << user << std::endl;
	std::cout << cmd << std::endl;

	return 0;
}