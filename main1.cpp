/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:17 by ddiakova          #+#    #+#             */
/*   Updated: 2022/04/30 15:40:47 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

int     main()
{
	std::cout << "** Complete command line with all 4 parts: prefix, command word, parameters, trailer **" << std::endl;
	std::string line = "!avf Join #test,#bou,&coucou mo,na :oisj dgf oisd/r/n";

	Command     cmd(line);
	std::cout << cmd << std::endl;

	std::cout << "** Command with command word, parameters, trailer **" << std::endl;
	std::string line1 = "JOIN #test,#bou,&coucou mo,na :oisj dgf oisd/r/n";

	Command     cmd1(line1);
	std::cout << cmd1 << std::endl;

	std::cout << "** Command with command word, parameters **" << std::endl;
	std::string line2 = "JOIN #test,#bou,&coucou mo,na/r/n";

	Command     cmd2(line2);
	std::cout << cmd2 << std::endl;

	std::cout << "** Command with command word only **" << std::endl;
	std::string line3 = "JOIN/r/n";

	Command     cmd3(line3);
	std::cout << cmd3 << std::endl;

	std::cout << "** Command with command word, trailer **" << std::endl;
	std::string line4 = "JOIN :oisj dgf oisd/r/n";

	Command     cmd4(line4);
	std::cout << cmd4 << std::endl;

	return 0;
}