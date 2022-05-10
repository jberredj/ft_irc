/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesombe <abesombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:24:41 by abesombe          #+#    #+#             */
/*   Updated: 2022/04/03 18:58:25 by abesombes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.cpp"
#include "utils.cpp"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
	/* ---------- INITIALIZING VARIABLES ---------- */

	/*
		 1. client/server are two file descriptors
		 These two variables store the values returned
		 by the socket system call and the accept system call.
		 2. portNum is for storing port number on which
		 the accepts connections
		 3. isExit is bool variable which will be used to
		 end the loop
		 4. The server reads characters from the socket
		 connection into a dynamic variable (buffer).
		 5. A sockaddr_in is a structure containing an internet
		 address. This structure is already defined in netinet/in.h, so
		 we don't need to declare it again.
			DEFINITION:
			struct sockaddr_in
			{
				short   sin_family;
				u_short sin_port;
				struct  in_addr sin_addr;
				char    sin_zero[8];
			};
			6. serv_addr will contain the address of the server
			7. socklen_t  is an intr type of width of at least 32 bits
	*/
	string hostname = "irc.server.com";
	string server_address = "127.0.0.1";
	int port_num = generateRandPortNum();
	server serv(hostname, server_address, port_num);
	cout << "port_num: " << port_num << endl;
	int bufsize = 512;
	char buffer[bufsize];
	char reply[bufsize];

	/* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
	/* --------------- socket() function ------------------*/

	serv.createSocket();

	/* ---------- BINDING THE SOCKET ---------- */
	/* ---------------- bind() ---------------- */

	if (serv.bindSocket() < 0)
		return (-1);

	/* ------------- LISTENING CALL ------------- */
	/* ---------------- listen() ---------------- */

	serv.listenSocket();
	/* ------------- ACCEPTING CLIENTS  ------------- */
	/* ----------------- listen() ------------------- */

	int server = serv.acceptConnection();
	int clientCount = 1;

	while (server > 0) {
		std::cout << "=> Connected with the client #" << clientCount
							<< ", you are good to go..." << std::endl;

		/*
				Note that we would only get to this point after a
				client has successfully connected to our server.
				This reads from the socket. Note that the read()
				will block until there is something for it to read
				in the socket, i.e. after the client has executed a
				the send().
				It will read either the total number of characters
				in the socket or 1024
		*/

		int bytes_received = 0;
		int flag = 1;

		std::string tmp;
		do
		{
			bytes_received = recv(server, buffer, bufsize, 0);
			if (bytes_received > 0)
			{
				cout << "bytes received: " << bytes_received << endl;
				buffer[bytes_received] = '\0';
				std::string s(buffer);
				tmp = tmp + s;
				cout << "tmp: \n" << tmp << endl;
				string command = "NICK";
				string space = "\n";
				int nick_pos = tmp.find(command);
				// cout << "nick_pos: " << nick_pos << endl;
				if (nick_pos != -1)
				{
					int pos_next_space = tmp.find(space, nick_pos + 5) - nick_pos - 6;
					// cout << "position of the next space: " << pos_next_space << endl;
					string nickname = tmp.substr(nick_pos + 5, pos_next_space);
					// cout << "NICK tag detected: [" << nickname << "]\n";
					string tmp_reply;
					string reply_code = "001";
					tmp_reply = ":" + hostname + " " + reply_code + " " + nickname + " " +
											":Welcome to IRC Server " + nickname + "!" + nickname +
											"@127.0.0.1\r\n";

					int bytes_sent = tmp_reply.length();
					// cout << "tmp_reply: " << tmp_reply << endl;
					// tmp_reply = ":" + hostname + reply_code + " * " + nickname +
					//            "Nickname is already in use.";
					if (!tmp_reply.empty() && flag)
					{
						cout << "sending back a reply to IRC client\n";
						strcpy(reply, tmp_reply.c_str());
						// strcat(reply, "\r\n\0");
						// printf("reply: %s", reply);
						send(server, reply, bytes_sent, 0);
						tmp_reply = "";
						flag = 0;
					}
				}
			}
		} while (true);

		/* ---------------- CLOSE CALL ------------- */
		/* ----------------- close() --------------- */

		/*
				Once the server presses # to end the connection,
				the loop will break and it will close the server
				socket connection and the client connection.
		*/

		// inet_ntoa converts packet data to IP, which was taken from client
		cout << "\n\n=> Connection terminated with IP "
				 << inet_ntoa(serv.getServerAddr().sin_addr);
		close(server);
		cout << "\nGoodbye..." << endl;
		// isExit = false;
		exit(1);
	}

	close(serv.getClient());
	return 0;
}
