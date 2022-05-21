*/-/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:19:33 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/19 16:37:02 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <vector>
# include "User.hpp"


class Channel
{
public:
	Channel(void);
	Channel(const Channel &src);
	~Channel(void);

	Channel	&operator=(const Channel &rhs);


	bool	addUser(User *newUser);
	bool	addUser(std::string nickname);
	bool	removeUser(User *user);
	bool	removeUser(std::string nickname);
//	bool	mode(User *user, std::string mode)

private:
	std::string			_name;
	std::string			_topic;
	std::vector<User *>	_users; 
//	std::map<User*, std::string> _mode; ??? map each user pointer to mode string
//	Add a deletion mechanism
};


#endif