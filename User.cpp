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

User::User(void) : command_buf(""), command_queue(), response_queue(), cmd(), _status(REGISTER),
		_username("daria"), _nickname("kukuruzka"), _truename(""), _hostname(""), _servaddr(""),  _mode("w"),
		_prevnick(""), _channel("")
{
	cmd["WHOIS"] = WHOIS;
	cmd["USERS"] = USERS;
	cmd["USER"] = USER;
	cmd["TOPIC"] = TOPIC;
	cmd["PRIVMSG"] = PRIVMSG;
	cmd["PONG"] = PONG;
	cmd["PPING"] = PING;
	cmd["PASS"] = PASS;
	cmd["PART"] = PART;
	cmd["OPER"] = OPER;
	cmd["NICK"] = NICK;
	cmd["NAMES"] = NAMES;
	cmd["MODE"] = MODE;
	cmd["LIST"] = LIST;
	cmd["KILL"] = KILL;
	cmd["KICK"] = KICK;
	cmd["JOIN"] = JOIN;
	cmd["INVITE"] = INVITE;
	cmd["PBAN"] = BAN;
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
	// std::queue<Command *> trash = std::queue<Command *>();
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