//
// Created by karin on 13/01/2020.
//

#include <iostream>
#include "MySerialServer.h"
#include "ServerSide.h"
#include "MySerialServer.h"
using namespace std;
using namespace server_side;
using namespace boot;

int main(int argc, char *argv[]) {
    Main main1 = Main();
    string argsad = argv[1];
    main1.main(2, argv);
    return 0;
}