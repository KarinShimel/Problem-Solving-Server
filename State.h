//
// Created by karin on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_STATE_H
#define SEARCHALGO_COMP_STATE_H

#include <string.h>
#include <string>

using namespace std;

template<class T>
class State {
private:
    string name; // Name of state
    T state;
    double cost; // Cost to state
    State<T> * cameFrom; // The state it came from
public:
    State(string name1, T state1) {
        this->name = name1;
        this->state = state1;
        //this->cameFrom = from;
    }
    State(){

    }
    void setFrom( State<T> from){
        this->cameFrom = &from;
    }
    void setCost(double cost1) {
        this->cost = cost1;
    }
    double getCost(){
        return this->cost;
    }
    T getState(){
        return this->state;
    }

    bool operator==(const State<T> &s) const {
        //this->name.compare(s.name) && strcmp(this->cameFrom.state, s.cameFrom.state
        return (this->state== s.state);
    }
};


#endif //SEARCHALGO_COMP_STATE_H
