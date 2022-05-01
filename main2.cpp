/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:39:44 by ddiakova          #+#    #+#             */
/*   Updated: 2022/04/30 15:40:15 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int     main(int ac, char **av)
{
	std::string line;
	line = std::string(av[1]);
	(void)ac;

	Command     cmd(line);
	std::cout << cmd << std::endl;

	return 0;
}