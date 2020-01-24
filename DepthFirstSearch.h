//
// Created by karin on 21/01/2020.
//

#ifndef SEARCHALGO_COMP_DEPTHFIRSTSEARCH_H
#define SEARCHALGO_COMP_DEPTHFIRSTSEARCH_H
#include "Searcher.h"
#include <algorithm>

template<class Problem, class Solution>
class DepthFirstSearch : public Searcher<Problem, Solution> {
public:
    Solution search(MySearchable<Problem> searchable) {
        State<Problem> goal;
        goal = DFSSearch(searchable);
        // Creating the path
        return getPath(goal,searchable);
    }
    string getPath(State<Problem> goal, MySearchable<Problem> searchable){
        stack<string> pathQ;
        while(!((goal)== searchable.getInitial()) ) {
            State<Problem>* from = goal.cameFrom;
            string a = searchable.findDirection((goal),*from);
            pathQ.push(a);
            goal = *from;
        }
        string path;
        while (!pathQ.empty()) {
            path += pathQ.top();
            path += ", ";
            pathQ.pop();
        }
        path.resize(path.size()-2);
        return path;
    }

    int getNumberOfNodesEvaluated() {

    }

    State<Problem> DFSSearch(MySearchable<Problem> searchable) {
        State<Problem> start = searchable.getInitial();
        stack<State<Problem>> stack;
        stack.push(start);
        list<State<Problem>> visited;
        list<Problem> visitedPoint;
        visitedPoint.push_back(start.getState());
        start.setVisited();
        State<Problem> curr1 ;
        while (!stack.empty()) {
            State<Problem>* curr = &(stack.top());
            stack.pop();
            // If its the goal state
            if (searchable.isGoal(*curr))
                return *curr;
            // If not - getting the neighbors
            list<State<Problem>> neighbors = searchable.getAllPossibleStates(*curr);
            for (State<Problem> neighbor1 : neighbors) {
                State<Problem>* neighbor = &neighbor1;
                // If we didnt visit the neighbor
                bool neighborVisited = false;
                for (Problem problem : visitedPoint) {
                    bool k = (problem == neighbor1.getState());
                    if (k) {
                        neighborVisited = true;
                    }
                }
                if (!neighborVisited) {
                    neighbor->setVisited();
                    visitedPoint.push_back(neighbor->getState());
                    stack.push(*neighbor);
                }
            }
        }
        visited.clear();
    }
};
#endif //SEARCHALGO_COMP_DEPTHFIRSTSEARCH_H
