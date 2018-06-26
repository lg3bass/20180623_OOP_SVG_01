#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "Shape.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void advanceShape(ASDR state);
    
        bool rAltKey;
        bool rShiftKey;
    
        int altIndex;
        int shiftIndex;
    
    ofxSVG svg;
    float step;
    vector<ofPolyline> outlines;
    
    vector<Shape> shapes;
    int currentShape;
    float pct;
};
