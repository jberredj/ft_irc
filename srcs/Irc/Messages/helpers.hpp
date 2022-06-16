/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:35:48 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/16 22:05:11 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_HPP
# define HELPERS_HPP
# include "Command.hpp"

bool		needMoreParams(Command &command, size_t minRequired);
std::string	getNameFromList(std::string& nameList);
#endif