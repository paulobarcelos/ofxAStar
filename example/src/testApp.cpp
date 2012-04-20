#include "testApp.h"

void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // Load an image to be used as a map
    mapImage.loadImage("Stockholm.png"); // todo - currently only working with square images
    // Create the map from the image
    map.setup(mapImage);
    // Initialize the path finder
    pathfinder.setup(&map);
    
    // Get all the free nodes from the map and select 2 of them to be used
    // as a start and end points for a path
    vector<ofVec2f> freeNodesCoordinates = map.getFreeNodesCoordinates();
    start = freeNodesCoordinates[(rand()%freeNodesCoordinates.size())-1];
    end = freeNodesCoordinates[(rand()%freeNodesCoordinates.size())-1];
    
    // Find the path
    vector<ofVec2f>* foundPath = pathfinder.findPath(start, end);
    
    // If the path was found, convert the coordinates to ofPoints so we 
    // can feed them to an ofPolyline
    if(foundPath){
        cout << foundPath->size() << endl;
        vector<ofPoint> vertexes;
        for (int i = 0; i < foundPath->size(); i++) {
            ofPoint vertex;
            vertex.x = (*foundPath)[i].x;
            vertex.y = (*foundPath)[i].y;
            vertexes.push_back(vertex);
        }
        path.addVertexes(vertexes);
    }
    
}

void testApp::draw(){
    ofSetColor(255);    
    mapImage.draw(0,0); 
    
    ofSetColor(255, 0, 0);
    path.draw();
    
    ofSetColor(0, 255, 0);
    ofCircle(start.x, start.y, 5);
    
    ofSetColor(0, 0, 255);
    ofCircle(end.x, end.y, 5);
    
}