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
    bool visited = false;
public:
    double cost; // Cost to state
    State<T>* cameFrom;
    State(string name1, T state1, double val) {
        this->name = name1;
        this->state = state1;
        this->value = val;
    }

    State() {

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
