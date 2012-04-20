#include "Map2D.h"

namespace ofxAStar {

    using namespace std;
        Map2D::Map2D(){
            map = NULL;
            // Just for safety
            allocate(1,1);
        }
        
        Map2D::~Map2D(){
            if(map) delete map;
            map = NULL;           
        }
        
        void Map2D::setup(ofImage bitmap){
            ofPixels_<unsigned char> pixelsRef;
            
            setup(bitmap.getPixelsRef().getChannel(0).getPixels(), bitmap.getWidth(), bitmap.getHeight());
            
        }
    
        void Map2D::setup(unsigned char * data, unsigned int width, unsigned int height){
            int size = width * height;
            allocate(width, height, false);
            for (unsigned int i = 0; i < size; i++) {
                if(data[i] < 1) map[i] = false;
                else map[i] = true;
            }
            computeNodesCoordinates();
        }
        
        void Map2D::allocate(unsigned int width, unsigned int height, bool computeNodes) {
            if(map) delete map;
            this->width = width;
            this->height = height;
            unsigned int size = width * height;
            map = new bool[size];
            if(computeNodes){
                for (int i = 0; i < size; i++) {
                    map[i] = false;
                }
                computeNodesCoordinates(); 
            }            
            
        }
        
        void Map2D::computeNodesCoordinates() {
            freeNodesCoordinates.clear();
            blockedNodesCoordinates.clear();
            for(int y = 0; y < height; y++){
                for(int x = 0; x < width; x++){
                    ofVec2f nodeCoordinates;
                    nodeCoordinates.x = x;
                    nodeCoordinates.y = y;
                    if(get(x,y)){
                        blockedNodesCoordinates.push_back(nodeCoordinates);
                    }
                    else{
                        freeNodesCoordinates.push_back(nodeCoordinates);
                    }
                }
            }
        }
        
        int Map2D:: get(int x, int y){
            if(x < 0 || x >= width || y < 0 || y >= height){
                return false;	 
            }            
            return map[(y*height)+x];
        }
        
        bool Map2D::set(int x, int y, bool value){
            if(x < 0 || x >= width || y < 0 || y >= height){
                return false;	 
            }
            map[(y*height)+x] = value;
            return true;
        }
        
        vector<ofVec2f> Map2D::getFreeNodesCoordinates(){
            return freeNodesCoordinates;
        }
        
        vector<ofVec2f> Map2D::getBlockedNodesCoordinates(){
            return blockedNodesCoordinates;
        }
};