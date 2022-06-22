/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:45:54 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/22 22:59:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_HPP
# define TYPEDEFS_HPP
# include <string>
# include <vector>
# include "types/Nullptr_t.hpp"
# define INSPIRCD_MAX_LEN 64
# include <poll.h>
class Channel;
class User;
typedef std::vector<Channel*>::iterator channelIterator;
typedef std::vector<pollfd> pollfds;
typedef pollfds::iterator pollfdsIterator;
typedef std::vector<User*>	userVec;
typedef std::vector<std::string> strVec;


#endif