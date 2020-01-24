//
// Created by karin on 21/01/2020.
//

#ifndef SEARCHALGO_COMP_BESTFIRSTSEARCH_H
#define SEARCHALGO_COMP_BESTFIRSTSEARCH_H

#include "Searcher.h"
template <class Problem,class Solution>
class BestFirstSearch : public Searcher<Problem,Solution>{

    // a class for the priority queue order
    class StateComparator{
    public:
        bool operator()(State<Problem>* left, State<Problem>* right){
            return (left->getTotalCost() > right->getTotalCost());
        }
    };

public:
    BestFirstSearch(){
        this->evaluatedNodes = 0;
        this->pathCost = 0;
    }

    /*
    * this method reality the Best search first algorithm
    */
    vector<State<Problem>*> search(MySearchable<Problem> *searchable) override {
        this->initialization();
        State<Problem>* curS =searchable->getInitState();
        //the end state
        State<Problem>* endS =searchable->getGoalState();

        priority_queue<State<Problem>*, vector<State<Problem>*>, StateComparator> openPQueue;
        curS->setTotalCost(curS->getCost());
        openPQueue.push(curS);

        while (!openPQueue.empty()){
            //see the object in the front of the queue
            curS = openPQueue.top();
            openPQueue.pop();
            //this->evaluatedNodes ++;
            if (!curS->getIsMarked()){
                this->evaluatedNodes ++;
            }
            curS->setIsMarked(true);
            //we check if we arrive the end and found our path
            if(curS->equals(endS)){
                break;
            }

            // get all the possible states that adjacent to current state
            vector<State<Problem>*> possibleStates = searchable->getPossibleStates(curS);
            long upToCost = curS->getTotalCost();
            for (int i = 0; i < possibleStates.size(); i++) {
                State<Problem>* adj = possibleStates[i];
                // calculate the total path cost for this adj
                long adjFutureTotalCost = adj->getCost() + upToCost;
                // if the total cost is -1- we didnt get to thus node yet;
                if(adj->getTotalCost() == -1 || adj->getTotalCost() > adjFutureTotalCost){
                    adj->setCameFrom(curS);
                    adj->setTotalCost(adjFutureTotalCost);
                    // update the queue order
                    if (adj->getTotalCost() > adjFutureTotalCost) {
                        openPQueue = updatePriorityOrder(openPQueue);
                    } else{
                        openPQueue.emplace(adj);
                    }
                }

            }
        }
        return this->findPath(searchable->getGoalState());
    }

    /**
     * this function orders the priority queue
     * @param curQueue
     * @return new priority queue
     */
    priority_queue<State<Problem>*, vector<State<Problem>*>, StateComparator> updatePriorityOrder
    (priority_queue<State<Problem>*, vector<State<Problem>*>, StateComparator> curQueue){
        priority_queue<State<Problem>*, vector<State<Problem>*>, StateComparator> newQueue;
        while (!curQueue.empty()){
            State<Problem>* temp = curQueue.top();
            curQueue.pop();
            newQueue.emplace(temp);
        }
        return newQueue;
    }

};

#endif //SEARCHALGO_COMP_BESTFIRSTSEARCH_H
