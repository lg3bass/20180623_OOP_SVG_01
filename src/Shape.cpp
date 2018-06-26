//
//  Shape.cpp
//  20180623_OOP_SVG_01
//
//  Created by Robert White III on 6/23/18.
//

#include "Shape.h"

//-------------------------------------------------
Shape::Shape(ofPolyline s){

    originalShape = s;
    modifiedShape = s;
    
    life = 100;
    alpha = 100;
    
    pct = 0.0;    
    playing = false;
}

//-------------------------------------------------
void Shape::update(){

    //life--;
}

//-------------------------------------------------
void Shape::draw(){
    if(playing){
        
        switch(state){
            case ASDR::attack:
                //cout << "attack " << ofToString(modifiedShape.getCentroid2D()) << endl;
                
                ofPushMatrix();
                    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
                
                    //get location of original centroid
                    centX = originalShape.getCentroid2D().x-(ofGetWidth()/2);
                    centY = originalShape.getCentroid2D().y-(ofGetHeight()/2);

                    //move to original centroids
                    ofTranslate(centX, centY);
                    ofScale(pct,pct,pct);
                
                    modifiedShape.draw();
                
                ofPopMatrix();
                
                //debug - draw the centroid
                ofDrawCircle(originalShape.getCentroid2D().x, originalShape.getCentroid2D().y, 10);
                
                ofPushStyle();
                    ofSetColor(0);
                    //ofDrawBitmapString(instance, originalShape.getBoundingBox().x, originalShape.getBoundingBox().y+20);
                    ofDrawBitmapString(instance, originalShape.getCentroid2D().x-4, originalShape.getCentroid2D().y+4);
                ofPopStyle();
                
                pct += 0.05;
                if(pct > 1.0){
                    state = ASDR::decay;
                    pct = 0;
                }
                break;
            case ASDR::decay:
                
                ofPushStyle();
                
                ofSetColor(255, 0, 200, ofMap(pct,0,1.0,255,0));
                    ofBeginShape();
                        for( int i = 0; i < originalShape.getVertices().size(); i++) {
                            ofVertex(originalShape.getVertices().at(i).x, originalShape.getVertices().at(i).y);
                        }
                    ofEndShape();
                ofPopStyle();
                
                pct += 0.15;
                if(pct > 1){
                    state = ASDR::sustain;
                    pct = 0.0;
                }
                
                originalShape.draw();
                
                break;
            case ASDR::sustain:
                //cout << "sustain" << pct << endl;
                
                originalShape.draw();
                
                break;
            case ASDR::release:
                //cout << "release " << pct << endl;
                
                //modifiedShape = modifiedShape.getResampledBySpacing(6);
                modifiedShape = originalShape.getResampledBySpacing(10);
                modifiedShape = modifiedShape.getSmoothed(pct);
                
                pct += 1.0;
                if(pct > 100.0){
                    playing = false;
                    state = ASDR::stop;
                    pct = 0;
                }
                
                modifiedShape.draw();
                
                break;
            case ASDR::stop:
                cout << "stop " << pct << endl;

                break;
        }
    
        /*
        //fill the shape (old way - https://forum.openframeworks.cc/t/fill-polyline/10800)
        ofBeginShape();
            for( int i = 0; i < temp.getVertices().size(); i++) {
                ofVertex(temp.getVertices().at(i).x, temp.getVertices().at(i).y);
            }
        ofEndShape();
        */
    }
}

//-------------------------------------------------
Boolean Shape::finished(){
    if(life == 0){
        return true;
    } else {
        return false;
    }
}

//-------------------------------------------------
void Shape::play(int i){
    
    instance = i;
    modifiedShape = originalShape;
    
    //interate through the points and move the centroid
    //forum.openframeworks.cc/t/scaling-a-mesh-centred-anchor-point-ofmesh-ofscale-oftranslate/20309
    for(int i=0;i<modifiedShape.size();i++){
        modifiedShape.getVertices()[i] = originalShape.getVertices()[i] - originalShape.getCentroid2D();
    }
    
    playing = true;
    pct = 0.0;
}

//-------------------------------------------------
void Shape::release(){
    
    state = ASDR::release;
    pct = 0.0;
}
