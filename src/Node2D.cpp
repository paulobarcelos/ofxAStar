#include "Node2D.h"

namespace ofxAStar {

    void Node2D::PrintNodeInfo() {
        ofLogVerbose() << "Node position : (" << x << ", " << y << ")";
    }

    bool Node2D::IsSameState( Node2D &rhs ){
        // same state in a maze search is simply when (x,y) are the same
        if( (x == rhs.x) && (y == rhs.y) ){
            return true;
        }
        else{
            return false;
        }
    }

    

    // Here's the heuristic function that estimates the distance from a Node
    // to the Goal. 

    float Node2D::GoalDistanceEstimate( Node2D &nodeGoal ){
        float xd = fabs(float(((float)x - (float)nodeGoal.x)));
        float yd = fabs(float(((float)y - (float)nodeGoal.y)));
        
        return xd + yd;
    }

    bool Node2D::IsGoal( Node2D &nodeGoal ){
        
        if( (x == nodeGoal.x) &&
           (y == nodeGoal.y) )
        {
            return true;
        }
        
        return false;
    }

    // This generates the successors to the given Node. It uses a helper function called
    // AddSuccessor to give the successors to the AStar class. The A* specific initialisation
    // is done for each node internally, so here you just set the state information that
    // is specific to the application
    bool Node2D::GetSuccessors( AStarSearch<Node2D> *astarsearch, Node2D *parent_node ){
        
        int parent_x = -1; 
        int parent_y = -1; 
        
        if( parent_node )
        {
            parent_x = parent_node->x;
            parent_y = parent_node->y;
        }
        
        Node2D * newNode;
        
        // push each possible move except allowing the search to go backwards        
        if(!map->get( x-1, y ) && !(parent_x == x-1  && parent_y == y)){
            newNode = new Node2D( map, x-1, y );
            astarsearch->AddSuccessor( *newNode );
        }	
        
        if(!map->get( x, y-1 ) && !(parent_x == x && parent_y == y-1)){
            newNode = new Node2D( map, x, y-1 );
            astarsearch->AddSuccessor( *newNode );
        }	
        
        if(!map->get( x+1, y ) && !(parent_x == x+1 && parent_y == y)){
            newNode = new Node2D( map, x+1, y );
            astarsearch->AddSuccessor( *newNode );
        }        
        
        if(!map->get( x, y+1 ) && !(parent_x == x && parent_y == y+1)){
            newNode = new Node2D( map, x, y+1 );
            astarsearch->AddSuccessor( *newNode );
        }	
        
        return true;
    }

    // given this node, what does it cost to move to successor. In the case
    // of our map the answer is the map terrain value at this node since that is 
    // conceptually where we're moving

    float Node2D::GetCost( Node2D &successor ) {
        return ( map->get( x, y ) ) ? 0.f : 1.f;
    }
};