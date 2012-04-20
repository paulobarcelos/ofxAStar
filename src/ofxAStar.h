#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ofMain.h"
#include "stlastar.h"
#include "Map2D.h"
#include "Node2D.h"

namespace ofxAStar {

    class Pathfinder2D {
        
    public:
        
        Pathfinder2D(){
            map = NULL;  
        };
        
        ~Pathfinder2D(){
            map = NULL;  
        };
        
        void setup(Map2D* map){
            this->map = map;
        };
        
        vector<ofVec2f>* findPath(ofVec2f& start, ofVec2f& end){         
            AStarSearch<Node2D> astarsearch;
            
            unsigned int SearchCount = 0;
            
            const unsigned int NumSearches = 1;
            
            
            vector<ofVec2f>* path = new vector<ofVec2f>();
            bool searchSuccess = true;
            
            while(SearchCount < NumSearches){
                
                // Create a start state
                Node2D nodeStart = Node2D(map, start.x, start.y);
                
                // Define the goal state
                Node2D nodeEnd = Node2D(map, end.x, end.y);
                
                // Set Start and goal states               
                astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);
                
                unsigned int SearchState;
                unsigned int SearchSteps = 0;
                
                do{
                    SearchState = astarsearch.SearchStep();
                    
                    SearchSteps++;                    
                }
                while( SearchState == AStarSearch<Node2D>::SEARCH_STATE_SEARCHING );
                
                if( SearchState == AStarSearch<Node2D>::SEARCH_STATE_SUCCEEDED ){
                    ofLogVerbose() << "Search found goal state\n";
                    
                    Node2D *node = astarsearch.GetSolutionStart();
                    
                    int steps = 0;
                    
                    for( ;; )
                    {
                        node = astarsearch.GetSolutionNext();
                        
                        if( !node ){
                            break;
                        }
                        
                        ofVec2f vert;
                        vert.x = node->x;
                        vert.y = node->y;
                        
                        path->push_back(vert); 
                        
                        node->PrintNodeInfo();
                        steps ++;
                        
                    };
                    
                    ofLogVerbose() << "Solution steps " << steps;
                    
                    // Once you're done with the solution you can free the nodes up
                    astarsearch.FreeSolutionNodes();
                    
                    
                }
                else if( SearchState == AStarSearch<Node2D>::SEARCH_STATE_FAILED ) 
                {
                    ofLogVerbose() << "Search terminated. Did not find goal state";
                    searchSuccess = false;
                }
                
                // Display the number of loops the search went through
                ofLogVerbose() << "SearchSteps : " << SearchSteps;
                
                SearchCount ++;
                
                astarsearch.EnsureMemoryFreed();
            }
            return path;
            
            if(searchSuccess) return path;
            else return NULL;

        };
    private:
        Map2D* map;
    };
};