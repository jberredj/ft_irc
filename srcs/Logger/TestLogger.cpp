/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestLogger.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:33:34 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/11 01:30:49 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include <iostream>

int main(void)
{
	Logger::addOutput(&std::cout, "stdout");
	Logger(Output::DEBUG) << 12854;
	Logger(Output::DEBUG) << 12854;
	Logger(Output::DEBUG) << 12854;
	Logger(Output::DEBUG) << 12854;
	return 0;
}