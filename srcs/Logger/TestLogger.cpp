/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestLogger.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:33:34 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/11 11:19:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include <iostream>

int main(void)
{
	Logger::addOutput(&std::cout, "stdout");
	Logger::addOutput("test.log");
	Logger::currentTimeAddOutput("test.log");
	Logger(Output::DEBUG) << 12854;
	Logger(Output::DEBUG) << 12854;
	Logger(Output::DEBUG) << 12854;
	Logger(Output::DEBUG) << 12854;
	return 0;
}