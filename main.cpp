//
// Created by karin on 13/01/2020.
//

#include "MySerialServer.h"
#include "ServerSide.h"

using namespace std;
using namespace server_side;
using namespace boot;


    int main(int argc, char *argv[]) {
        Main main1 = Main();
        main1.main(argc, argv);
        return 0;
    }