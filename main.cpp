//
// Created by karin on 13/01/2020.
//

#include <iostream>
#include <fstream>
#include "MySerialServer.h"
#include "ServerSide.h"
#include "MySerialServer.h"

using namespace std;
using namespace server_side;
using namespace boot;

vector<vector<int>> createVec(string filename) {
    vector<vector<int>> matVector;
    vector<int> lineVector;
    int len, number;
    string line;
    ifstream file;
    file.open(filename);
    int firstDigit, lastDigit;
    string notDigitOptions = {',', ' '};
    string digitOptions = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    if (!file.is_open()) {
        cout << "Unable to open file\n" << endl;
    } else {
        while (!file.eof()) {
            getline(file, line);
            len = line.length();
            lineVector.clear();//clear data (of last line)
            for (int i = 0; i < len;) {
                firstDigit = line.find_first_not_of(notDigitOptions, i);
                lastDigit = line.find_first_not_of(digitOptions, firstDigit);
                lastDigit = lastDigit - 1; //index of last digit in number
                if (firstDigit != -1 && lastDigit != -1) {
                    number = stoi(line.substr(firstDigit, (lastDigit - firstDigit)));
                    lineVector.push_back(number);
                } else {
                    break;//there are no more numbers
                }
                i = lastDigit + 1;
            }
            matVector.push_back(lineVector);
        }

    }
    cout<<"------------PRINT MAT---------------"<<endl;
    for (int i=0;i<matVector.size();i++){
        for (int j=0; j<matVector[i].size();j++){
            cout<< matVector[i][j]<<",";
        }
        cout<<""<<endl;
    }
}

    int main(int argc, char *argv[]) {
        Main main1 = Main();
        string argsad = argv[1];
        main1.main(2, argv);
        return 0;
    }