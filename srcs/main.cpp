/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:12:10 by jberredj          #+#    #+#             */
/*   Updated: 2022/08/06 17:14:10 by jberredj         ###   ########.fr       */
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
	Logger::addOutput(&std::cout, "stdout", Output::INFO);
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
	delete ServerInstance;
	Logger::clearOutputs();
	return 0;
}
