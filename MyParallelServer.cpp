//
// Created by karin on 24/01/2020.
//

#include <thread>
#include <mutex>
#include "MyParallelServer.h"
extern std::mutex mutex_lock;

void MyParallelServer::open(int port, ClientHandler *client_handler) {
    bool stop = false;
    ClientHandler *cH = client_handler;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
    }

    //bind socket to IP address new
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) {
        std::cerr << "Error during listening command" << std::endl;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    thread myThread(&MyParallelServer::start, this, socketfd, address, cH, stop);
    myThread.join();
}

void MyParallelServer::start(int socketfd, sockaddr_in address, ClientHandler *client_handler, bool stop) {
    cout << "Parallel server waiting for clients.." << endl;
    while (!stop) {
        int addrlen = sizeof(address);
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
            int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
            if (client_socket == -1) {
                std::cerr << "can't accept client" << std::endl;
                return;
            }
            thread myThread(&MyParallelServer::handleForThread, this, socketfd,client_socket, client_handler);
            myThread.detach();
        }
    }
}

void MyParallelServer::handleForThread(int socketfd, int client_socket, ClientHandler *clientHandler) {
    mutex_lock.lock();
    clientHandler->handleClient(socketfd, client_socket);
    mutex_lock.unlock();
}