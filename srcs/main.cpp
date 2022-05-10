/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:12:10 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/10 18:09:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include "IrcServ.hpp"
#include "User.hpp"
#include "typedefs.hpp"
#include "Logger.hpp"
#include <string>


const ft::Nullptr ft::null_ptr;

int main(int ac, char **av)
{
	Logger::logToCout(Logger::TRACE);
	std::ostream *test = Logger::createLogFile("test.log", Logger::DEBUG);
	Logger::closeLogger(test);
	Logger::closeLogger(test);
	// Logger::closeLogger("test.log");
	// Logger::closeLogger("test.log");
	IrcServ *ServerInstance = ft::null_ptr;
	try
	{
		ServerInstance = new IrcServ(ac, av);
	}
	catch (const std::exception &e)
	{
		Logger::fatal(e.what());
		Logger::destroy();
		return 1;
	}
	User::initUserClass();
	ServerInstance->run();
	(void)ac;
	(void)av;
	delete ServerInstance;
	Logger::destroy();
	return 0;
}
