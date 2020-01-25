//
// Created by karin on 21/01/2020.
//

#ifndef SEARCHALGO_COMP_BESTFIRSTSEARCH_H
#define SEARCHALGO_COMP_BESTFIRSTSEARCH_H

#include <queue>
#include "Searcher.h"

#include "Searcher.h"
#include "algorithm"

template<class Problem, class Solution>
class BestFirstSearch : public Searcher<Problem, Solution> {

    class StateComparator {
    public:
        bool operator()(State<Problem> *left, State<Problem> *right) {
            return (left->getCost() > right->getCost());
        }
    };

public:
    int nodesEvaluated = 0;

    BestFirstSearch() {}

    string getPath(State<Problem> goal, MySearchable<Problem> searchable) {
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

    vector<State<Problem> *> search(MySearchable<Problem> *searchable) override {
        this->initialization();
        State<Problem> *curr = searchable->getInitial();
        State<Problem> *goal = searchable->getGoalState();

        priority_queue < State<Problem> * , vector<State<Problem> *>, StateComparator > openPQueue;
        openPQueue.push(curr);

        while (!openPQueue.empty()) {
            curr = openPQueue.top();
            openPQueue.pop();
            nodesEvaluated++;

            curr->setVisited(true);
            if (curr==goal) {
                return getPath(curr);
            }

            // get all the possible states from this state
            vector<State<Problem> *> possibleStates = searchable->getPossibleStates(curr);
            long upToCost = curr->getCost();
            for (int i = 0; i < possibleStates.size(); i++) {
                State<Problem> *adj = possibleStates[i];
                long adjFutureTotalCost = adj->getCost() + upToCost;

                if (adj->getCost() > adjFutureTotalCost) {
                    adj->setFrom(curr);
                    adj->setCost(adjFutureTotalCost);
                    if (adj->getCost() > adjFutureTotalCost) {
                        openPQueue = updatePriorityOrder(openPQueue);
                    } else {
                        openPQueue.emplace(adj);
                    }
                }
            }
        }
        return getPath(searchable->getGoalState());
    }

    priority_queue<State<Problem> *, vector<State<Problem> *>, StateComparator> updatePriorityOrder
            (priority_queue<State<Problem> *, vector<State<Problem> *>, StateComparator> curQueue) {
        priority_queue < State<Problem> * , vector<State<Problem> *>, StateComparator > newQueue;
        while (!curQueue.empty()) {
            State<Problem> *temp = curQueue.top();
            curQueue.pop();
            newQueue.emplace(temp);
        }
        return newQueue;
    }

};

#endif //SEARCHALGO_COMP_BESTFIRSTSEARCH_H
