#pragma once

#include "ofMain.h"
#include "ofxAStar.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    
    ofImage mapImage;
    ofxAStar::Map2D map;
    ofxAStar::Pathfinder2D pathfinder;
    
    ofVec2f start, end;
    ofPolyline path;
};
