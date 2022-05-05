#include "User.hpp"


void WHOIS(Command *cmd);
void USERS(Command *cmd);
void USER(Command *cmd);
void TOPIC(Command *cmd);
void PRIVMSG(Command *cmd);
void PONG(Command *cmd);
void PING(Command *cmd);
void PASS(Command *cmd);
void PART(Command *cmd);
void OPER(Command *cmd);
void NICK(Command *cmd);
void NAMES(Command *cmd);
void MODE(Command *cmd);
void LIST(Command *cmd);
void KILL(Command *cmd);
void KICK(Command *cmd);
void JOIN(Command *cmd);
void INVITE(Command *cmd);
void BAN(Command *cmd);


void    User::addResponse(std::string response)
{
    response_queue.push(response);
}

void    User::applyCmd()
{

}


std::ostream & operator<<(std::ostream & o, User const & rhs)
{
    o << "Username: " << rhs.getUsername() << std::endl;
	o << "Nickname: " << rhs.getNickname() << std::endl;
	o << "Mode: " << rhs.getMode() << std::endl;
    return o;
}