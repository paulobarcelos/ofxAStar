#pragma once

#include "ofMain.h"

namespace ofxAStar {
    class Map2D{
    public:
        Map2D();        
        ~Map2D();
        
        void setup(ofImage bitmap);
        void setup(unsigned char * data, unsigned int width, unsigned int height);
        
        void allocate(unsigned int width, unsigned int height, bool computeNodes = true);
        
        int get(int x, int y);        
        bool set(int x, int y, bool value);
        
        vector<ofVec2f> getFreeNodesCoordinates();        
        vector<ofVec2f> getBlockedNodesCoordinates();
        
    private:
        bool* map;
        unsigned int width, height;
        vector<ofVec2f> freeNodesCoordinates;
        vector<ofVec2f> blockedNodesCoordinates;
        void computeNodesCoordinates();
    };
};