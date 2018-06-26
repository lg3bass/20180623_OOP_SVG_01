#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofBackground(0);
    
    //load the svg
    svg.load("vmm_square4.svg");
    
    //loop through file pull out layers
    for (int i = 0; i < svg.getNumPath(); i++){
        ofPath p = svg.getPathAt(i);
        // svg defaults to non zero winding which doesn't look so good as contours
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
        for(int j=0;j<(int)lines.size();j++){
            shapes.push_back(lines[j].getResampledBySpacing(1));
        }
    }
    
    currentShape = -1;
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0;i<shapes.size();i++){
        shapes[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //on-screen
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    ofDrawBitmapString("currentShape: " + ofToString(currentShape),20,40);
    
    ofPushMatrix();
        //draw all the shapes
        for(int i=0;i<shapes.size();i++){
            shapes[i].draw();
        }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        
        advanceShape(ASDR::attack);
    } else if(key == '1'){
        
        advanceShape(ASDR::attack);
    } else if(key == '2'){
        
        advanceShape(ASDR::decay);
    } else if(key == '3'){
        
        advanceShape(ASDR::sustain);
    } else if(key == '4'){
        
        advanceShape(ASDR::release);
    } else if(key == OF_KEY_RIGHT_ALT){
        
        cout << "Right Alt/Opt Pressed" << endl;
        rAltKey = true;
        advanceShape(ASDR::attack);
        altIndex = currentShape;
        
    } else if(key == OF_KEY_RIGHT_SHIFT){
        
        cout << "Right Shift Pressed" << endl;
        rShiftKey = true;
        advanceShape(ASDR::attack);
        shiftIndex = currentShape;
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == OF_KEY_RIGHT_ALT){
        
        cout << "Right Alt/Opt Released" << endl;
        rAltKey = true;
        shapes[altIndex].release();

    } else if(key == OF_KEY_RIGHT_SHIFT){
        
        cout << "Right Shift Released" << endl;
        rShiftKey = true;
        shapes[shiftIndex].release();
        
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::advanceShape(ASDR state){
    
    if(currentShape < shapes.size()-1){
        currentShape++;
    } else {
        currentShape = 0;
    }
    
    
    cout << "playing shape " << currentShape << endl;
    
    shapes[currentShape].state = state;
    shapes[currentShape].play(currentShape);
}
