//
// Created by karin on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_STATE_H
#define SEARCHALGO_COMP_STATE_H

#include <string.h>
#include <string>
#include <list>
#include <iostream>

using namespace std;

template<class T>
class State {
private:

    string name; // Name of state
    T state;
    double value;
    double cost; // Cost to state
    bool visited = false;
    double shortestPathCost;

    //typedef State<T> cameFrom;
public:
    State<T>* cameFrom;
    State(string name1, T state1, double val) {
        this->name = name1;
        this->state = state1;
        this->value = val;
        //this->cameFrom = from;
    }

    State() {

    }
    void setShortesPathCost(double val){
        this->shortestPathCost = val;
    }
    double getShortestPathCost(){
        return this->shortestPathCost;
    }

    void setVisited() {
        this->visited = true;
    }

    bool getVisited() {
        return this->visited;
    }

    void setFrom(State<T> *from) {
        if (from != NULL) {
            this->cameFrom = from;
            this->cost = from->getCost() + this->value;
        }
    }

    State<T>* getFrom() {
        this->cameFrom;
    }

    void setCost(double cost1) {
        this->cost = cost1;
    }

    double getCost() {
        return this->cost;
    }

    T getState() {
        return this->state;
    }


    bool operator==(const State<T> &s) const {
        //this->name.compare(s.name) && strcmp(this->cameFrom.state, s.cameFrom.state
        return (this->state == s.state);
    }

    ostream &print(ostream &out) {
        auto obj = this->getState();
        out << obj;
        return out;
    }
    ~State(){}
};

#endif //SEARCHALGO_COMP_STATE_H
