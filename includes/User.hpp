/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:15:25 by ddiakova          #+#    #+#             */
/*   Updated: 2022/06/18 15:55:40 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include <string>
# include <queue>
# include <map>

class Command;

class User
{
public:
	enum			Status {PASSWORD, REGISTER, ONLINE, AWAY, OFFLINE, DELETE};

	// Constructors and destructor
					User(void);
					User(const User& src);
					User(std::string* serverPassWd);
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
	std::string		getMode(void) const;
	std::string		getAwaymsg(void) const; 
	bool			repliesAvalaible(void) const;
	
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
	void			setMode(std::string mode);
	void			setAwayMsg(std::string msg);

	// IO User methods
	void			addCommand(const Command& command);
	void			execCommandQueue(void);
	void			addReply(std::string reply);
	std::string		getReplies(void);
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
	std::string 										_mode;
	std::string											_awayMsg;
	time_t												_signon;

	// Init user Class
	static void											_initUserClass(void);
	static std::map<std::string, void (*)(Command&)>	_cmdMap;
	static bool											_inited;
};

std::ostream&	operator<<(std::ostream& o, const User & rhs);

#endif