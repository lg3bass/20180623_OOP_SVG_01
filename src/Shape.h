//
//  Shape.h
//  20180623_OOP_SVG_01
//
//  Created by Robert White III on 6/23/18.
//

#include "ofMain.h"

enum ASDR {attack, decay, sustain, release, stop};

class Shape {
    
    public:
    
    Shape(ofPolyline s);
    
    void update();
    void draw();
    Boolean finished();
    void play(int i);
    void release();
    
    int instance;

    ofPolyline originalShape;
    ofPolyline modifiedShape;
    
    float life;
    float alpha;
    
    float pct;
    
    float scale;
    
    float centX;
    float centY;
    string centLoc;
    
    bool playing;
    
    ASDR state = stop;
    
};
