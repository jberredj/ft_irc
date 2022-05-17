/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:16:57 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/17 09:19:55 by jberredj         ###   ########.fr       */
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

	// getReply functions
	std::string getReply(int code, std::vector<std::string> args);
	std::string getReply(std::string (*func)(std::vector<std::string>),
					std::vector<std::string> args);
private:
	std::map<int, std::string (*)(std::vector<std::string>)>	_replies;

	// Init function
	void	_initRepliesMap(void);
};

#endif