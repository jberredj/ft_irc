/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:15:25 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/23 00:35:16 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include <string>
# include <queue>
# include <map>
# include "UserMode.hpp"

class Command;
class Channel;

class User
{
public:
	enum			Status {PASSWORD, REGISTER, ONLINE, OFFLINE, DELETE};

	// Constructors and destructor
					User(void);
					User(const User& src);
					~User(void);

	//operators
	User&			operator=(const User& rhs);

	//getters
	Status			getStatus(void) const;
	std::string		getUsername(void) const;
	std::string		getNickname(void) const;
	std::string		getHostname(void) const;
	std::string		getTruename(void) const;
	std::string		getCommandBuf(void) const;
	std::string		getPrefix(void) const;
	std::string		getSignon(void) const;
	std::string		getRawSignon(void) const;
	std::string		getIdle(void) const;
	std::string		getModesList(void) const;
	std::string		getAwaymsg(void) const;
	bool			repliesAvalaible(void) const;
	bool			isOperator(void) const;

	//setters
	void			setStatus(Status status);
	void			setPassword(std::string password);
	void			setUsername(std::string username);
	void			setNickname(std::string nickname);
	void			setHostname(std::string hostname);
	void			setTruename(std::string truename);
	void			setCommandBuf(std::string commandBuf);
	void			clearCommandBuff(void);
	void			appendCommandBuf(std::string commandBuf);
	void			setAwayMsg(std::string msg);
	void			addMode(uint8_t mode);
	void			removeMode(uint8_t mode);
	bool			hasMode(uint8_t mode);

	std::vector<Channel*>	getChannels(void);
	void			addChannelToUser(Channel *channel);
	void			removeChannelFromUser(Channel *channel);
	void			clearChannels(void);

	// IO User methods
	void			addCommand(const Command& command);
	void			clearCommandQueue(void);
	void			execCommandQueue(void);
	void			addReply(std::string reply);
	std::string		getReplies(void);
	void			clearReplies(void);
	void			tryAuthentificate(Command &cmd);
	bool			isAway(void);

private:
	std::string 										_commandBuf;
	std::queue<Command> 								_commandQueue;
	std::queue<std::string>								_responseQueue;
	
	// User infos
	Status 												_status;
	std::string											_password;
	std::string 										_username;
	std::string 										_nickname;
	std::string 										_truename;
	std::string 										_hostname;
	UserMode 											_modes;
	std::string											_awayMsg;
	time_t												_signon;
	std::vector<Channel*>								_channels;

	// Init user Class
	static void											_initUserClass(void);
	static std::map<std::string, void (*)(Command&)>	_cmdMap;
};

std::ostream&	operator<<(std::ostream& o, const User & rhs);

#endif