#include "User.hpp"

void WHOIS(Command *command){(void)command;}
void USERS(Command *command){(void)command;}
void USER(Command *command){(void)command;}
void TOPIC(Command *command){(void)command;}
void PRIVMSG(Command *command){(void)command;}
void PONG(Command *command){(void)command;}
void PING(Command *command){(void)command;}
void PASS(Command *command){(void)command;}
void PART(Command *command){(void)command;}
void OPER(Command *command){(void)command;}
void NICK(Command *command){(void)command;}
void NAMES(Command *command){(void)command;}
void MODE(Command *command){(void)command;}
void LIST(Command *command){(void)command;}
void KILL(Command *command){(void)command;}
void KICK(Command *command){(void)command;}
void JOIN(Command *command){(void)command;}
void INVITE(Command *command){(void)command;}
void BAN(Command *command){(void)command;}

User::User(void) : command_buf(""), command_queue(), response_queue(), cmd_map(), _status(REGISTER),
		_username("daria"), _nickname("kukuruzka"), _truename(""), _hostname(""), _servaddr(""),  _mode("w"),
		_prevnick(""), _channel("")
{
	cmd_map["WHOIS"] = WHOIS;
	cmd_map["USERS"] = USERS;
	cmd_map["USER"] = USER;
	cmd_map["TOPIC"] = TOPIC;
	cmd_map["PRIVMSG"] = PRIVMSG;
	cmd_map["PONG"] = PONG;
	cmd_map["PPING"] = PING;
	cmd_map["PASS"] = PASS;
	cmd_map["PART"] = PART;
	cmd_map["OPER"] = OPER;
	cmd_map["NICK"] = NICK;
	cmd_map["NAMES"] = NAMES;
	cmd_map["MODE"] = MODE;
	cmd_map["LIST"] = LIST;
	cmd_map["KILL"] = KILL;
	cmd_map["KICK"] = KICK;
	cmd_map["JOIN"] = JOIN;
	cmd_map["INVITE"] = INVITE;
	cmd_map["PBAN"] = BAN;
	std::cout << "user constructor called" << std::endl;
}

void    User::addResponse(std::string response)
{
    response_queue.push(response);
}

void    User::apply()
{
	// UStatus status = _status;

	// if (status == DELETE)
	// 	return ;
	while (1)
	{	
		Command cmd = command_queue.front();
		command_queue.pop();
		if (cmd_map.count(cmd.getCommand()))
			cmd_map[cmd.getCommand()];
		else
			std::cout << "Uknown command: " << cmd.getCommand() << std::endl;
		apply();
	}	
	// std::queue<Command *>::iterator it = command_queue.begin();
	// for ()

	// std::string	cmd = trash.front();
	// trash.pop();

	//gestion d'erreur
	//if (success)
		//exec cmd
	//else
		//trash.push(cmd);
}

std::ostream & operator<<(std::ostream & o, User const & rhs)
{
    o << "Username: " << rhs.getUsername() << std::endl;
	o << "Nickname: " << rhs.getNickname() << std::endl;
	o << "Mode: " << rhs.getMode() << std::endl;
    return o;
}