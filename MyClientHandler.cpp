//
// Created by karin on 14/01/2020.
//
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>

#include "MyClientHandler.h"
#include "MySearchable.h"
#include "State.h"
#include "ObjectAdapter.h"

using namespace std;

void MyClientHandler::handleClient(int serverSocket, int clientSocket) {
    //std::cout << "Handling ..." << std::endl;
    vector<vector<int>> matVector;
    vector<int> lineVector;
    int len, number;
    string line;
    int firstDigit, lastDigit;
    string notDigitOptions = {',', ' '};
    string digitOptions = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    // Reading the data till 'end'
    int lines = 0;
    int cols = 0;
    while (true) {
        char buffer[1024] = {0};
        int valread = read(clientSocket, buffer, 1024);
        std::string a(buffer);
        len = strlen(buffer);
        line = buffer;
        if (a.find("end") != std::string::npos) {
            // Finished the data
            break;
        } else {
            lineVector.clear();//clear data (of last line)
            for (int i = 0; i < len;) {
                firstDigit = line.find_first_not_of(notDigitOptions, i);
                lastDigit = line.find_first_not_of(digitOptions, firstDigit + 1);
                if (firstDigit != -1) {
                    number = stoi(line.substr(firstDigit, (lastDigit - firstDigit)));
                    lineVector.push_back(number);
                } else {
                    break;//there are no more numbers
                }
                i = lastDigit;
                if (lines == 0)
                    cols++;
            }
            matVector.push_back(lineVector);
        }

        lines++;
        //std::cout << a << '\n';
    }
    lines -= 3;
    cols -= 1;
    cout << lines << "," << cols << endl;
    /*cout << "------------PRINT MAT---------------" << endl;
    for (int i = 0; i < matVector.size(); i++) {
        for (int j = 0; j < matVector[i].size(); j++) {
            cout << matVector[i][j] << "  ";
        }
        cout << "" << endl;
    }*/


    // Creating the problem
    MySearchable<Point> matrixSearchable = MySearchable<Point>(matVector);
    matrixSearchable.setMaxLines(lines);
    matrixSearchable.setMaxCols(cols);
    // Tests !!!!!!
    /*matrixSearchable.setGoal(36, 36);
    Point p = Point(0, 0);
    bool a = matrixSearchable.isGoal(State<Point>("36,36", p));
    if (a) {
        cout << "its true" << endl;
    }
    State<Point> testState = State<Point>("0,0",p);
    testState.setCost((double)matVector.at(0).at(0));
    list <State<Point>> list= matrixSearchable.getAllPossibleStates(testState);
    cout<<"From (0,0) we can reach:"<<endl;
    for(State<Point> point  : list){
            cout<<"Possible state: "<< point.getState().getI()<<","<< point.getState().getJ()<<" at a cost of: "<< point.getCost()<<endl;
    }*/

    // The Shit Happens Here !!!!!!!!!!!!!!!!!!!!!
    //ObjectAdapter<vector<vector<int>>, string> objectAdapter = ObjectAdapter<vector<vector<int>>, string>(
     //       matrixSearchable);
    // Creating a solution
    // If the solution is in the cache manager
    // If the solution is not in the cache manager - we will solve the problem
    // Updating the solution in the cache manager
}