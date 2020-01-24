//
// Created by karin on 21/01/2020.
//

#ifndef PART2_ASTAR_H
#define PART2_ASTAR_H



#include "Searcher.h"
#include "Searcher.h"
#include "algorithm"
using namespace std;

template<class Problem, class Solution>
class AStar:public Searcher< Problem, Solution>{
public:
    int NodesEvaluated = 0;
    vector<State<Problem>*> opened;
    virtual int getNumberOfNodesEvaluated(){
        return this->NodesEvaluated;
    }
/**
 * search for the shortest
 * @param searchable
 * @return the path
 */
    Solution search(MySearchable<Problem> searchable) {
        opened.clear();
        vector<State<Problem>> closed;
        // Setting the goal and initial states
        State<Problem> goal = (searchable.getGoalState());
        State<Problem> start = (searchable.getInitial());
        list<Problem> visitedPoint;
        State<Problem>* goalViaASTAR;
        double f = abs(start.getState().getI()-goal.getState().getI())
                   +abs(start.getState().getJ()-goal.getState().getJ());
        start.setShortesPathCost(start.getCost());
        this->opened.push_back(&start);
        while(!(this->opened.empty())){
            State<Problem>* curr = this->findingMinVal(&goal);
            curr->setVisited();
            visitedPoint.push_back(curr->getState());
            closed.push_back(*curr);
            // if we reached our goal
            if(*(curr) == goal){
                cout<<"HERE"<<endl;
                break;
            }
            this->NodesEvaluated++;
            list<State<Problem>> neighbors = searchable.getAllPossibleStates(*curr);
            for (State<Problem> neighbor1 : neighbors) {
                State<Problem>* temp = &neighbor1;
                temp->setShortesPathCost(temp->getCost());
                bool neighborVisited = false;
                for (Problem problem : visitedPoint) {
                    bool k = (problem == neighbor1.getState());
                    if (k) {
                        neighborVisited = true;
                    }
                }
                if(neighborVisited)
                    continue;
                double currPath = curr->getShortestPathCost()+temp->getCost();
                if( find(this->opened.begin(),this->opened.end(),temp)!=this->opened.end()) {
                    if (temp->getShortestPathCost() < currPath)
                        continue;
                } else if(find(closed.begin(),closed.end(),*temp)!=closed.end()){
                    if (temp->getShortestPathCost() < currPath)
                        continue;
                }else{
                    temp->setShortesPathCost(currPath);
                    temp->setFrom(curr);
                    this->opened.push_back(temp);
                }
            }
            goalViaASTAR = curr;
        }
        goalViaASTAR->setCost(goalViaASTAR->getShortestPathCost());
        return getPath(*goalViaASTAR,searchable);
        /*

         vector<State<Problem>*> returnVal;
         State<Problem>* currentState = searchable->getGoalState();
         State<Problem>* beginState = searchable->getInitialState();
         if(currentState->getDad()==NULL){
             return returnVal;
         }
         //loop that create the path
         while (!beginState->Equal(currentState)){
             returnVal.push_back(currentState);
             currentState = currentState->getDad();
         }
         returnVal.push_back(searchable->getInitialState());

         std::reverse(returnVal.begin(),returnVal.end());

         *//*
        cout<<"astar"<<endl;
        cout<<goal->getShortestPathVal()<<endl;
        cout<<this->nodeThatEleveted<<endl;*//*
        return returnVal;*/
        return "BLA";
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
    /**
     * the priority queue
     * @param goal
     * @return
     */
    State<Problem>* findingMinVal(State<Problem>* goal) {
        vector<State<Point>*> temp;

        State<Point>* lowest = opened.back();
        opened.pop_back();

        double heuristic = abs(lowest->getState().getI() - goal->getState().getI())
                          +abs(lowest->getState().getJ() - goal->getState().getJ());
        double first =lowest->getShortestPathCost()+ heuristic ;

        while(!this->opened.empty()){
            State<Point>* state = opened.back();
            opened.pop_back();


            heuristic = abs(state->getState().getI()- goal->getState().getI())
                       +abs(state->getState().getJ() - goal->getState().getJ());
            double cost = state->getShortestPathCost() +heuristic ;

            if(cost<first){
                first = cost;
                temp.push_back(lowest);
                lowest = state;
                continue;
            }
            temp.push_back(state);
        }
        for(int i = 0 ; i < temp.size();i++){
            this->opened.push_back(temp[i]);
        }
        return lowest;
    }

    void popFrom(State<Problem>* temp,vector<State<Problem>> close){
        vector<State<Problem>*> move;
        typename vector<State<Problem>*>::iterator it;
        it = close->begin();
        for(;it !=close->end();++it){
            State<Problem>* now = close->back();
            close->pop_back();
            move.push_back(now);
            if(now->Equal(temp)){
                this->opened.push_back(now);
                return;
            }
        }

    }

};
#endif //PART2_ASTAR_H
