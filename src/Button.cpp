//
//  Button.cpp
//
//  Created by Let it Brain on 03/12/2015.
//
//

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Button.h"


//--------------------------------------------------------------
Button::Button(){
    

    
    buttColor.set(150, 30, 10);
    activeColor.set(30,150,10);
    lineColor.set(200, 100, 80, 255);

    bActive = false;
    bEvent = false;
    bPitch = NULL;
    bState = false;
    bLastButtState = false;
    bPreviousStatus = NULL;

    
    buttonRect.setPosition(0, 0);
    
    timer = 0;
    
//    iconPath = "";
//    buttonIcon.load("images/" + iconPath);

}

//--------------------------------------------------------------
void Button::update(){
    

    
}

//--------------------------------------------------------------
void Button::loadFont(string fontName, float size){
    
    text.load(fontName, size);

}

//----------------------------------rectangle---------------------
void Button::draw(float x, float y, float width, float height, string label){
    
    buttonRect.set(x,y, width, height);        //rectangle button
//    ofRectangle textRect = text.getStringBoundingBox(label, buttonRect.getCenter().x,
//                                                     buttonRect.getCenter().y); //rectangle Label

    ofFill();
    
//    ofPushStyle();
//    if (bActive == true) {
//        ofSetColor(activeColor);
//    } else if (bActive == false) {
//        ofSetColor(buttColor);
//    }
//        ofDrawEllipse(buttonRect.x + width/2, buttonRect.y + height/2, width, height);
//    
//    ofPopStyle();

        buttonIcon.load("images/" + label);
        buttonIcon.draw(buttonRect.x , buttonRect.y, width,height);
/*
        labelColor.set(255);
        ofSetColor(labelColor);
        text.drawString(label, buttonRect.getCenter().x - textRect.getWidth()/2,
                        buttonRect.getCenter().y + textRect.getHeight()/2);
 
    
    //line around rectangle
    ofNoFill();
    ofSetColor(lineColor);
    ofSetLineWidth(2);
    ofDrawEllipse(buttonRect.x, buttonRect.y, width, height);
 
 */

}


//-------------------------------ellipse----------------------
/*
void Button::draw(float x, float y, float width, float height, string label){
    
    buttonRect.set(x,y, width, height);        //rectangle button
    ofRectangle textRect = text.getStringBoundingBox(label, buttonRect.getCenter().x,
                                                     buttonRect.getCenter().y); //rectangle Label
    
    ofFill();
    
    ofPushMatrix();
    ofTranslate(buttonRect.width/2, buttonRect.height/2);
    
    if (bActive == true) {
        
        ofSetColor(activeColor);
        ofDrawEllipse(buttonRect.x,buttonRect.y, buttonRect.width, buttonRect.height);
        
        labelColor.set(255);
        ofSetColor(labelColor);
        text.drawString(label, buttonRect.x - textRect.getWidth()/2,
                        buttonRect.y + textRect.getHeight()/2);
        
    }
    if(bActive == false) {
        
        ofSetColor(buttColor);
        ofDrawEllipse(buttonRect.x,buttonRect.y, buttonRect.width, buttonRect.height);
        
        labelColor.set(0);
        ofSetColor(labelColor);
        text.drawString(label, buttonRect.x - textRect.getWidth()/2,
                        buttonRect.y + textRect.getHeight()/2);
    }
    
    //line around rectangle
    ofNoFill();
    ofSetColor(lineColor);
    ofSetLineWidth(2);
    ofDrawEllipse(buttonRect.x,buttonRect.y, buttonRect.width, buttonRect.height);
    ofPopMatrix();

//    ofDrawRectangle(buttonRect);
}
 */

//--------------------------------------------------------------
void Button::keyReleased(int key)  {
    
}

//--------------------------------------------------------------
void Button::mouseReleased(int x, int y, int button)  {
    
}

//--------------------------------------------------------------
ofRectangle Button::getRectangle() {
    
    return buttonRect;
}
//--------------------------------------------------------------
void Button::setActiveColor(float r, float g, float b) {
    
    activeColor.set(r, g, b);

}
//--------------------------------------------------------------
void Button::setLabelColor(float r, float g, float b) {
    
    labelColor.set(r, g, b);
    
}
//--------------------------------------------------------------
void Button::setLabel(string s) {
    ofRectangle textRect = text.getStringBoundingBox(s, buttonRect.getCenter().x,
                                                     buttonRect.getCenter().y); //rectangle Label

    text.drawString(s, buttonRect.getCenter().x - textRect.getWidth()/2,
                    buttonRect.getCenter().y + textRect.getHeight()/2);
    
}
//--------------------------------------------------------------
void Button::setButtColor(float r, float g, float b) {
    
    buttColor.set(r, g, b);
    
}
//--------------------------------------------------------------
void Button::setButtColor(float r, float g, float b, float a) {
    
    buttColor.set(r, g, b, a);
    
}
//--------------------------------------------------------------
void Button::setbActive(bool b) {
    
    bActive = b;
}

//--------------------------------------------------------------
bool Button::getbActive() {
    
    return bActive;
}
//--------------------------------------------------------------
bool Button::getbEvent() {
    
    return bEvent;
}
//--------------------------------------------------------------
void Button::setbEvent(bool b) {
    
    bEvent = b;
}
//--------------------------------------------------------------
bool Button::getPreviousStatus() {
    
    return bPreviousStatus;
}
//--------------------------------------------------------------
void Button::setTimer(long t) {
    
    timer = t;
}

//--------------------------------------------------------------
void Button::TimerIncrease() {
    
    timer++;
}
//--------------------------------------------------------------
void Button::TimerDecrease() {
    
    timer--;
}

//--------------------------------------------------------------
long Button::getTimer() {
    
   return timer;
}


//--------------------------------------------------------------
void Button::setbPitch(bool b) {
    
    bPitch = b;
}
//--------------------------------------------------------------
bool Button::getbPitch() {
    
    return bPitch;
}




#endif



















