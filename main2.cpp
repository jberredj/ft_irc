/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:39:44 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/05 15:48:25 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
#include "User.hpp"

int     main(int ac, char **av)
{
	std::string line;
	line = std::string(av[1]);
	(void)ac;

	Command     cmd(line);
	User		user("Daria", "daria", "w");
	std::cout << user << std::endl;
	std::cout << cmd << std::endl;

	return 0;
}