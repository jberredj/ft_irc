/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:19:33 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/19 12:36:14 by jberredj         ###   ########.fr       */
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


	void	addUser(User *newUser);
	void	addUser(std::string nickname);
private:
	std::vector<User *>	_users;

};


#endif