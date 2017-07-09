//
//  Button.h
//  100
//
//  Created by Let it Brain on 03/12/2015.
//
//

#include "ofMain.h"

class Button {
public:
    Button();
    void update();
    void loadFont(string fontName, float size);
    void draw(float x, float y, float width, float height, float roundness, string label);
    void draw(float x, float y, float width, float height, string label);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);

    
    ofRectangle getRectangle();
    void setLabel(string);
    void setButtColor(float, float, float);
    void setButtColor(float, float, float,float);
    void setActiveColor(float, float, float);
    void setLabelColor(float, float, float);
    void setbActive(bool);
    bool getbActive();
    void setbEvent(bool);
    bool getbEvent();
    bool getPreviousStatus();
    void setbPitch(bool);
    bool getbPitch();
    void setTimer(long);
    void TimerIncrease();
    void TimerDecrease();
    long getTimer();
    
private:
    ofVec2f pos;

    bool bActive, bEvent, bPitch, bState, bLastButtState, bPreviousStatus;
    
    ofColor buttColor, activeColor, labelColor, lineColor;
    string buttLabel;
    
    ofTrueTypeFont text;
    ofRectangle buttonRect;
    long timer;

};

