/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:16:57 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/17 01:23:28 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
# define REPLY_HPP
# include <vector>
# include <map>
# include <string>

class Reply
{
public:
	// Constructors and destructor
	Reply(void);
	Reply(const Reply &src);
	~Reply(void);

	// Operators
	Reply	&operator=(const Reply &rhs);
private:
	std::map<int, std::string (*)(std::vector<std::string>)>	_repliesMap;

	// Init function
	void	_initRepliesMap(void);
};

#endif