/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:48 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 22:42:45 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_HPP
# define HELPERS_HPP
# include "Command.hpp"

bool		needMoreParams(Command &command, size_t minRequired);
std::string	getNameFromList(std::string& nameList);
bool		validChannelName(std::string name);
#endif