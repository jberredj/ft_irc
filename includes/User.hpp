/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:15:25 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/17 01:17:11 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <algorithm>
#include "Command.hpp"
#include "Logger.hpp"
    
class User
{
	
	public:
		enum Status
		{
			PASSWORD,
			REGISTER,
			ONLINE,
			DELETE
		};
		User(void);
		User(User const & src);
		User(std::string *serverPassWd, std::vector<std::string> *nicksInUse) ;
		~User(void);
		//operators
		User 												&operator=(User const & rhs);

		//getters
		Status 												getStatus(void) const;
		std::string											&getServerPassword(void) const;
		std::string											getPassword(void) const;
		std::string											getUsername(void) const;
		std::string 										getNickname(void) const;
		std::string											getHostname(void) const;
		std::string 										getServaddr(void) const;
		std::string 										getTruename(void) const;
		std::string 										getCommandBuf(void) const;

		std::string											getMode(void) const;
		std::string											getPrevnick(void) const;
		std::string											getChannel(void) const;
		// std::string getAwaymsg(void) {return this->_awaymsg;}
		// std::string getDeletemsg(void) {return this->_deletemsg;}

		bool												searchNick(std::string nick);
		void 												reName(std::string nick);
		//setters
		void												setStatus(Status status);
		void												setPassword(std::string password);
		void												setUsername(std::string username);
		void												setNickname(std::string nickname);
		void												setHostname(std::string hostname);
		void												setServaddr(std::string servaddr);
		void												setTruename(std::string truename);
		void												setCommandBuf(std::string commandBuf);
		void												appendCommandBuf(std::string commandBuf);
		
		void												setMode(std::string mode);
		void												setPrevnick(std::string prevnick);
		void												setChannel(std::string channel);
		// void	setAwaymsg(std::string awaymsg) {this->_awaymsg = awaymsg;}
		// void	setDeletemsg(std::string deletemsg) {this->_deletmsg = deletemsg;}

		void												addToqueue(Command const & command);
		void												apply(); // fn pour le traitement des commandes dans la queue;
		//fonction pour recevoir le msg de server;
		void 												addResponse(std::string response); // fn pour remplir le tableau des responses;

		static void											initUserClass(void);
	
	private:
		
		std::string 										_commandBuf;
		std::queue<Command> 								commandQueue;
		std::queue<std::string>								responseQueue;
		static std::map<std::string, void (*)(Command &)>	cmdMap;
		// time_t last_ping;
		
		//les infos sur USER:
		Status 												_status;
		std::string 										*_ServerPassword;
		std::vector<std::string>							*_nicksInUse;
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

std::ostream &  operator<<(std::ostream & o, User const & rhs);

#endif