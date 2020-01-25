//
// Created by karin on 24/01/2020.
//

#ifndef MILESTONE2_MYPARALLELSERVER_H
#define MILESTONE2_MYPARALLELSERVER_H

#include <unistd.h>
#include "ServerSide.h"
#include <iostream>
#include "CacheManager.h"
#include "MyClientHandler.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include<pthread.h>
#include <thread>


class MyParallelServer : public Server {


public:
    MyParallelServer(){}
    void open(int port ,ClientHandler* c) ;
    void startThread(int socketfd, sockaddr_in address, ClientHandler *cH, bool stop);
    void handleForThread(int client_socket ,int socketfd , ClientHandler *cH);
    ~MyParallelServer(){}
};


#endif //MILESTONE2_MYPARALLELSERVER_H
