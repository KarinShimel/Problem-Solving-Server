//
// Created by karin on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_ISEARCHABLE_H
#define SEARCHALGO_COMP_ISEARCHABLE_H

#include "State.h"
#include <list>
#include <vector>
template<class T>
class ISearchable {
public:
    virtual State<T> getInitial() = 0; // get initial state
    virtual bool isGoal(State<T>) = 0; // is the state given is the goal state
    virtual list<State<T>> getAllPossibleStates(State<T>) = 0; // get all the possible states that can be reached from this state
    virtual ~ISearchable(){}
};

#endif //SEARCHALGO_COMP_ISEARCHABLE_H
