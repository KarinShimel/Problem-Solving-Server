//
// Created by karin on 20/01/2020.
//

#ifndef SEARCHALGO_COMP_BREADTHFIRSTSEARCH_H
#define SEARCHALGO_COMP_BREADTHFIRSTSEARCH_H

#include "Searcher.h"
#include <algorithm>

template<class Problem, class Solution>
class BreadthFirstSearch : public Searcher<Problem, Solution> {
public:
    int nodesEvaluated = 0;

    Solution search(MySearchable<Problem> searchable) {
        State<Problem> goal;
        goal = BFSSearch(searchable);
        // Creating the path
        stack<string> pathQ;
        int steps = 0;
        while (!((goal) == searchable.getInitial())) {
            State<Problem> *from = goal.cameFrom;
            string a = searchable.findDirection((goal), *from);
            pathQ.push(a);
            goal = *from;
        }
        string path;
        while (!pathQ.empty()) {
            steps++;
            path += pathQ.top();
            path += ", ";
            pathQ.pop();
        }
        path.resize(path.size() - 2);
        return path;
    }

    int getNumberOfNodesEvaluated() {
        return this->nodesEvaluated;
    }

    State<Problem> BFSSearch(MySearchable<Problem> searchable) {
        State<Problem> start = searchable.getInitial();
        queue<State<Problem>> queue;
        queue.push(start);
        list<State<Problem>> visited;
        list<Problem> visitedPoint;
        visitedPoint.push_back(start.getState());
        start.setVisited();
        State<Problem> curr1;
        while (!queue.empty()) {
            nodesEvaluated++;
            State<Problem> *curr = &(queue.front());
            queue.pop();
            // If its the goal state
            if (searchable.isGoal(*curr))
                return *curr;
            // If not - getting the neighbors
            list<State<Problem>> neighbors = searchable.getAllPossibleStates(*curr);
            for (State<Problem> neighbor1 : neighbors) {
                State<Problem> *neighbor = &neighbor1;
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
                    queue.push(*neighbor);
                }
            }
        }
        visited.clear();
    }
};


#endif //SEARCHALGO_COMP_BREADTHFIRSTSEARCH_H
