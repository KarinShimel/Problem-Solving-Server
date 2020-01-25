//
// Created by karin on 13/01/2020.
//

#include <iostream>
#include <fstream>
#include "MySerialServer.h"
#include "ServerSide.h"
#include "MySerialServer.h"

std::mutex mutex_lock;
using namespace std;
using namespace server_side;
using namespace boot;


    int main(int argc, char *argv[]) {
        Main main1 = Main();
        main1.main(2, argv);
        return 0;
    }