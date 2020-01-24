//
// Created by karin on 13/01/2020.
//

#ifndef SEARCHALGO_COMP_MYSERIALSERVER_H
#define SEARCHALGO_COMP_MYSERIALSERVER_H

#include "ServerSide.h"

#include <list>
#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <queue>

using namespace std;
using namespace server_side;

class MySerialServer : public Server {
public:
    // !!!!!!!!!!!!!
    // The linker is making me put the implementation here
    void open(int port, ClientHandler *clientHandler) override {
        string port1 = to_string(port);
        const char *portNum = port1.c_str();
        unsigned short portShort = (unsigned short) strtoul(portNum, NULL, 0);
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd == -1) {
            //error
            std::cerr << "Could not create a socket" << std::endl;
            exit(-1);
        }
        // Bind the socket to an IP address
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(portShort);
        if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
            std::cerr << "Could not bind the socket to an IP" << std::endl;
            exit(-2);
        }
        //ng the socket listen
        while (true) {
            if (listen(socketfd, 5) == -1) {
                std::cerr << "Error during listening command" << std::endl;
                exit(-3);
            } else {
                std::cout << "Server is now listening ..." << std::endl;
            }
            // Making a timeout
            struct timeval tv;
            tv.tv_usec = 120;
            tv.tv_sec = 100;
            if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv) == -1) {
                throw "Failed with setting the socket timeOut !";
            }
            fd_set rfds;
            FD_ZERO(&rfds);
            FD_SET(socketfd, &rfds);
            int iResult = select(socketfd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);
            if (iResult == 0) {
                // Timed out
                std::cout << "Timed out" << std::endl;
                break;
            } else {
                // The socket did not time out and can accept a client
                sockaddr_in Caddress;
                int client_socket = accept(socketfd, (struct sockaddr *) &Caddress,
                                           (socklen_t *) &Caddress);
                if (client_socket == -1) {
                    std::cerr << "Error accepting client" << std::endl;
                    exit(-4);
                } else {
                    cout << "Accepted Client" << endl;
                }
                clientHandler->handleClient(socketfd, client_socket);
            }
        }
        close(socketfd);
    }

    void stop() override {

    }

};


#endif //SEARCHALGO_COMP_MYSERIALSERVER_H
