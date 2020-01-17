//
// Created by karin on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_MYSEARCHABLE_H
#define SEARCHALGO_COMP_MYSEARCHABLE_H

#include <vector>
#include "ISearchable.h"
#include "State.h"

class Point {
private:
    int i;
    int j;
public:
    int getI() {
        return this->i;
    }

    int getJ() {
        return this->j;
    }

    Point() {}

    Point(int line, int row) {
        this->i = line;
        this->j = row;
    }

    bool operator==(const Point &p) const {
        return (this->i == p.i && this->j == p.j);
    }
};
string createNameFromIJ(int i1, int j1) {
    // taking int i, int j and turning into -> "i,j"
    string iStr = to_string(i1);
    string jStr = to_string(j1);
    string result;
    result = iStr + "," + jStr;
    return result;
}

template<class T>
class MySearchable : public ISearchable<T> {
private:
    State<T> initial; // initial state
    State<T> goalState; // goals
    vector<vector<int>> matrix;
    int maxI;
    int maxJ;
public:
    MySearchable(vector<vector<int>> mat) {
        this->matrix = mat;
        this->initial = State<Point>("0,0", Point(0, 0));
        /*State<nullptr_t> nullState("null", nullptr);
        this->initial.setFrom(nullState);*/
    }

    void setGoal(int i1, int j1) {
        this->goalState = State<Point>(createNameFromIJ(i1, j1), Point(i1, j1));
    }

    State<T> getInitial() {
        return this->initial;
    }

    bool isGoal(State<T> aState) {
        return aState == this->goalState;
    }

    void setMaxLines(int lines) {
        this->maxI = lines;
    }

    void setMaxCols(int cols) {
        this->maxJ = cols;
    }


    State<T> createNewState(State<Point> currState, int i, int j) {
        // creating the new state - constructor(name,Point)
        State<T>  newState = (State<Point>(createNameFromIJ(i, j), Point(i, j)));
        // getting the cost from the current state to the new state
        newState.setCost(currState.getCost() + this->matrix.at(i).at(j));
        // setting the fact that the new state was reached by using this state
        newState.setFrom(currState);
        return newState;
    }

    list <State<T>> getAllPossibleStates(State<Point> state) {
        /* Given a state - a place in the matrix - we need to return a lost with all
             * the other spots in the matrix we can reach from this state
             * Since it is a matrix - the neighbors are in the adjacent cells in the matrix*/
        list <State<Point>> possibleStates;
        State<Point> currState = state;
        int i, j;
        i = currState.getState().getI();
        j = currState.getState().getJ();
        // Finding up i-1,j
        if (i > 0) { // Making sure we won't reach out of matrix bounds
            possibleStates.push_front(this->createNewState(currState,i - 1, j));
        }
        // Finding  down neighbor i+1,j
        if (i < this->maxI) {// Making sure we won't reach out of matrix bounds
            possibleStates.push_front(this->createNewState(currState,i + 1, j));
        }
        // Finding left i,j-1
        if (j > 0) {// Making sure we won't reach out of matrix bounds
            // if we are at j=0, there isn't a left cell
            possibleStates.push_front(this->createNewState(currState,i, j - 1));
        }
        // Finding right i,j+1
        if (j < this->maxJ) {
            possibleStates.push_front(this->createNewState(currState,i, j + 1));
        }
        return possibleStates;
    }
};

#endif //SEARCHALGO_COMP_MYSEARCHABLE_H
