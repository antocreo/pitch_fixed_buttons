#include "ButtonPulse.h"

//--------------------------------------------------------------
void ButtonPulse::setup(){
    
    ofSetCircleResolution(60);
    
    increment = 0;
}

//--------------------------------------------------------------
void ButtonPulse::update(int speedModulo, ofSoundPlayer &player, float incrementVariation){
    
//    if (ofGetFrameNum()%speedModulo == 0) {
//        
//        if (increment < incrementLimit) {
//            increment+=incrementVariation;
//        } else increment = 1;
//       
//    }

    
    if (ofGetFrameNum()%speedModulo == 0) {
        
        if (player.isPlaying()) {
            increment+=incrementVariation;
        } else increment = 0;
//        else if (increment >0 ) increment--;
        
    }

    
}

//--------------------------------------------------------------
void ButtonPulse::draw(float x, float y){
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);


    for (int i = 0; i < 10; i++) {
        ofPushStyle();
        ofFill();
        ofSetColor(atan(increment)*10*i, increment*i, 0, 25 * i / increment);
        ofDrawCircle(x,y, i * 5 * increment);
        ofPopStyle();
        
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(i - increment);
        ofSetColor(tan(increment)*20*i, increment*i*10, 0,  25 * i / increment);
        ofDrawCircle(x,y, i * 20 * log(increment));
        ofPopStyle();
        

    }
    ofDisableBlendMode();
    ofPopStyle();
}

//--------------------------------------------------------------
void ButtonPulse::drawPlay(float x, float y){
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    
    for (int i = 0; i < 10; i++) {
//        ofPushStyle();
//        ofFill();
//        ofSetColor(atan(increment)*10*i, increment*i, 0, 2*i * increment);
//        ofDrawCircle(x,y, i * 5 * increment);
//        ofPopStyle();
        
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(i - increment);
        ofSetColor(tan(increment)*20*i, increment*i*10, 0,  i * increment);
        ofDrawCircle(x,y, i * 20 * log(increment));
        ofPopStyle();
        
        
    }
    ofDisableBlendMode();
    ofPopStyle();
}


//--------------------------------------------------------------
void ButtonPulse::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ButtonPulse::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ButtonPulse::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ButtonPulse::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ButtonPulse::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ButtonPulse::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ButtonPulse::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ButtonPulse::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ButtonPulse::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ButtonPulse::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ButtonPulse::dragEvent(ofDragInfo dragInfo){ 
    
}