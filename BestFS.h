//
// Created by noam on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_BESTFS_H
#define SEARCHALGO_COMP_BESTFS_H

#include <queue>
#include "ISearcher.h"

template<class Problem, class Solution>
class BestFS : public ISearcher<Problem, Solution> {
public:
    Solution search(MySearchable<Problem> searchable) override {
        cout<< " Got here OK "<<endl;
        State<Problem> s = searchable.getInitial();
        s.print(cout);
        /*State<Problem> initialState;
        priority_queue <State<Problem>> open = searchable.getInitial();
        queue <State<Problem>> close;
        State<Problem> n, s;
        list<State<Problem>> adj;
        while (!open.empty()) {
            n = dequeue(open);
            close.push(n);
            if (n.isGoal()) {
                //backtrace path to n (through recorded parents) and return path
            }
            adj.clear();
            adj = searchable.getAllPossibleStates(n);
            bool isIn;
            for (auto item:adj) {
                isIn=false;
                //check if item isn't in open or close
                for (auto item1:open) {
                    if (item == item1) {
                        isIn = true;
                        break;
                    }
                }
                if (!isIn) {
                    for (auto item1:close) {
                        if (item == item1) {
                            isIn = true;
                            break;
                        }
                    }
                }
                if (!isIn){
                    item.setFrom(n);
                }
            }
        }*/
    }
     int getNumberOfNodesEvaluated() override {

    }
    ~BestFS(){}
};


#endif //SEARCHALGO_COMP_BESTFS_H
