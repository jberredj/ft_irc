#include "Command.hpp"

// creer objet user 
// un truc pour stocker un moreceau de commande 

//std::string line = "!avf Join #test,#bou,&coucou mo,na :oisj dgf oisd/r/n"; = > chercher CRLF
//object user recupere la commande et la stocke dans l'objet commande - string buffer - ok

//tableau de commandes dans user => std::queue ctr pours stocker les commandes - ok

//pas de fd a gerer

//pas de liste d'users - elle sera dans le server

//tableau de responses pour le server std::queue = > "send" - ok
// *les informations sur le user:
 		// UserStatus status = ENUM;
		// time_t last_ping;
		// std::string hostaddr;
		// std::string hostname;
		// std::string nickname;
		// std::string username;
		// std::string realname;

		// std::string mode;
		// std::string pastnick;
		// std::string lastChannel;
		// std::string deleteMessage;
		// std::string awayMessage;


// faire la fonction write pour remplir le tableau des responses - ok

// NE PAS FAIRE PUSH => server - ok

// fonction dispatch - le traitement des commandes dans commande queue

***************************************************************
// COMMAND CLASS
// fonction reply avec user
// void reply(User &user, unsigned short code, std::string*);

// std::vector<std::string> array = {arg1, arg2, arg3, arg4, arg5, arg6, arg7};
// return command->reply(432, {nickname});
***************************************************************

// liste des replies 

// std::map<int, std::string (getReply*)(std::string*)> replies;


// replies[205]->getReply(array)

