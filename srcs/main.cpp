/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:12:10 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/21 14:07:10 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include "Server.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "typedefs.hpp"
#include "Logger.hpp"
#include <string>


const ft::Nullptr ft::null_ptr;

int main(int ac, char **av)
{
	Logger::addOutput(&std::cout, "stdout", Output::DEBUG);
	Logger::addOutput("trace.log", Output::TRACE, Output::TRACE);
	Server *ServerInstance = ft::null_ptr;
	try
	{
		ServerInstance = new Server(ac, av);
	}
	catch (const std::exception &e)
	{
		Logger(Output::FATAL) << (e.what());
		Logger::clearOutputs();
		return 1;
	}
	ServerInstance->run();
	(void)ac;
	(void)av;
	delete ServerInstance;
	Logger::clearOutputs();
	return 0;
}
