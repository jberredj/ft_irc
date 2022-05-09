/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:08:17 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/09 22:09:02 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

int     main()
{

	User		user;
	
	std::cout << "** Complete command line with all 4 parts: prefix, command word, parameters, trailer **" << std::endl;
	std::string line = "!avf Join #test,#bou,&coucou mo,na :oisj dgf oisd/r/n";

	Command     cmd(&user, line);
	std::cout << cmd << std::endl;

	std::cout << "** Command with command word, parameters, trailer **" << std::endl;
	std::string line1 = "JOIN #test,#bou,&coucou mo,na :oisj dgf oisd/r/n";

	Command     cmd1(&user, line1);
	std::cout << cmd1 << std::endl;

	std::cout << "** Command with command word, parameters **" << std::endl;
	std::string line2 = "JOIN #test,#bou,&coucou mo,na/r/n";

	Command     cmd2(&user, line2);
	std::cout << cmd2 << std::endl;

	std::cout << "** Command with command word only **" << std::endl;
	std::string line3 = "JOIN/r/n";

	Command     cmd3(&user, line3);
	std::cout << cmd3 << std::endl;

	std::cout << "** Command with command word, trailer **" << std::endl;
	std::string line4 = "JOIN :oisj dgf oisd/r/n";

	Command     cmd4(&user,line4);
	std::cout << cmd4 << std::endl;

	return 0;
}