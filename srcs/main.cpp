/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:12:10 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/03 23:00:20 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include "IrcServ.hpp"
#include "typedefs.hpp"

const ft::Nullptr ft::null_ptr;

int main(int ac, char **av)
{
	IrcServ *ServerInstance = ft::null_ptr;
	try
	{
		ServerInstance = new IrcServ(ac, av);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << ServerInstance << std::endl;
	ServerInstance->run();
	(void)ac;
	(void)av;
	delete ServerInstance;
	return 0;
}
