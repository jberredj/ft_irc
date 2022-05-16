/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:15:25 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/16 18:59:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include <string>
# include <queue>
# include <map>
# include "Command.hpp"
 
class User
{
public:
	enum			Status {PASSWORD, REGISTER, ONLINE, DELETE};

	// Constructors and destructor
					User(void);
					User(const User& src);
					User(std::string* serverPassWd,
						std::vector<std::string>* nicksInUse);
					~User(void);

	//operators
	User&			operator=(const User& rhs);

	//getters
	Status			getStatus(void) const;
	std::string&	getServerPassword(void) const;
	std::string		getPassword(void) const;
	std::string		getUsername(void) const;
	std::string		getNickname(void) const;
	std::string		getHostname(void) const;
	std::string		getServaddr(void) const;
	std::string		getTruename(void) const;
	std::string		getCommandBuf(void) const;

	std::string		getMode(void) const;
	std::string		getPrevnick(void) const;
	std::string		getChannel(void) const;
	// std::string getAwaymsg(void) {return this->_awaymsg;}
	// std::string getDeletemsg(void) {return this->_deletemsg;}
	
	//setters
	void			setStatus(Status status);
	void			setPassword(std::string password);
	void			setUsername(std::string username);
	void			setNickname(std::string nickname);
	void			setHostname(std::string hostname);
	void			setServaddr(std::string servaddr);
	void			setTruename(std::string truename);
	void			setCommandBuf(std::string commandBuf);
	void			appendCommandBuf(std::string commandBuf);
	
	void			setMode(std::string mode);
	void			setPrevnick(std::string prevnick);
	void			setChannel(std::string channel);
	// void	setAwaymsg(std::string awaymsg) {this->_awaymsg = awaymsg;}
	// void	setDeletemsg(std::string deletemsg) {this->_deletmsg = deletemsg;}

	// IO User methods
	void			addCommand(const Command& command);
	void			execCommandQueue(void);
	void			addReply(std::string reply);

	// Init user Class
	static void		initUserClass(void);

private:
	static bool											_inited;
	std::string 										_commandBuf;
	std::queue<Command> 								_commandQueue;
	std::queue<std::string>								_responseQueue;
	static std::map<std::string, void (*)(Command&)>	_cmdMap;
	// time_t last_ping;
	
	// User infos
	Status 												_status;
	std::string*										_ServerPassword;
	std::vector<std::string>*							_nicksInUse;
	std::string											_password;
	std::string 										_username;
	std::string 										_nickname;
	std::string 										_truename;
	std::string 										_hostname;
	std::string 										_servaddr;

	std::string 										_mode;
	std::string 										_prevnick;
	std::string 										_channel;
	// std::string _awaymsg;
	// std::string _deletemsg; 														
};

std::ostream&	operator<<(std::ostream& o, const User & rhs);

#endif