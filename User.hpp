/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:15:25 by ddiakova          #+#    #+#             */
/*   Updated: 2022/05/07 17:46:02 by ddiakova         ###   ########.fr       */
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

enum UStatus
	{
		PASSWORD,
		REGISTER,
		ONLINE,
		DELETE
	};
    
class User
{
    public:
        User(void);
        User(User const & src)
		{
			*this = src;
		}
        User & operator = (User const & rhs)
		{
			if (this != &rhs)
			{
				this->_status = rhs._status;
				this->_username = rhs._username;
				this->_nickname = rhs._nickname;
				this->_hostname = rhs._hostname;
				this->_servaddr = rhs._servaddr;
				this->_truename = rhs._truename;
				this->_mode = rhs._mode;
				this->_prevnick = rhs._prevnick;
				this->_channel = rhs._channel;
			}
			return *this;
		}
        ~User() {std::cout << "user destructor called" << std::endl;}
		
		//getters
		UStatus getUstatus(void) {return this->_status;}
		std::string	getUsername(void) const {return this->_username;}
		std::string getNickname(void) const {return this->_nickname;}
		std::string	getHostname(void) const {return this->_hostname;}
		std::string getServaddr(void) const {return this->_servaddr;}
		std::string getTruename(void) const {return this->_truename;}
	
		std::string getMode(void) const {return this->_mode;}
		std::string getPrevnick(void) const {return this->_prevnick;}
		std::string getChannel(void) const {return this->_channel;}
		// std::string getAwaymsg(void) {return this->_awaymsg;}
		// std::string getDeletemsg(void) {return this->_deletemsg;}
		
		//setters
		void	setUstatus(UStatus status) {this->_status = status;}
		void	setUsername(std::string username) {this->_username = username;}
		void	setNickname(std::string nickname) {this->_nickname = nickname;}
		void	setHostname(std::string hostname) {this->_hostname = hostname;}
		void	setServaddr(std::string servaddr) {this->_servaddr = servaddr;}
		void	setTruename(std::string truename) {this->_truename = truename;}
		
		void	setMode(std::string mode) {this->_mode = mode;}
		void	setPrevnick(std::string prevnick) {this->_prevnick = prevnick;}
		void	setChannel(std::string channel) {this->_channel = channel;}
		// void	setAwaymsg(std::string awaymsg) {this->_awaymsg = awaymsg;}
		// void	setDeletemsg(std::string deletemsg) {this->_deletmsg = deletemsg;}

		void addToqueue(Command command);
		void apply(); // fn pour le traitement des commandes dans la queue;
        //fonction pour recevoir le msg de server;
        void addResponse(std::string response); // fn pour remplir le tableau des responses;
	
    private:
        std::string command_buf;
        std::queue<Command> command_queue;
        std::queue<std::string>response_queue;
		std::map<std::string, void (*)(Command*)> cmd_map;
		// time_t last_ping;
		
        //les infos sur USER:
        UStatus _status;
		std::string _username;
		std::string _nickname;
		std::string _truename;
		std::string _hostname;
		std::string _servaddr;

		std::string _mode;
		std::string _prevnick;
		std::string _channel;
		// std::string _awaymsg;
		// std::string _deletemsg; 
};

std::ostream &  operator<<(std::ostream & o, User const & rhs);

#endif