#pragma once

#include "ofMain.h"
#include "Map2D.h"
#include "stlastar.h"

namespace ofxAStar {
    using namespace std;
    class Node2D{
    public:
        unsigned int x;	 // the (x,y) positions of the node
        unsigned int y;	
        
        Node2D(){
            Node2D(new Map2D(), 0, 0);
        };
        Node2D(Map2D* map){
            Node2D(map, 0, 0);
        };
        Node2D(unsigned int x, unsigned int y){
            Node2D(new Map2D(), x, y);
        };
        Node2D(Map2D* map, unsigned int x, unsigned int y){
            this->map = map;
            this->x = x;
            this->y = y;
        };
        ~Node2D(){
            map = NULL;
            // todo - should check if map was created internally and if so, delete it
        };
        
        float GoalDistanceEstimate( Node2D &nodeGoal );
        bool IsGoal( Node2D &nodeGoal );
        bool GetSuccessors( AStarSearch<Node2D> *astarsearch, Node2D *parent_node );
        float GetCost( Node2D &successor );
        bool IsSameState( Node2D &rhs );
        
        void PrintNodeInfo(); 
    private:
        Map2D* map;
    };
};