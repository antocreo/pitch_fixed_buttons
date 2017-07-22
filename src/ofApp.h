#pragma once

#include "ofMain.h"
#include "Button.h"
#include "WriteFile.h"
#include "ButtonPulse.h"


#define NUM_TONES 14
#define MAX_SEQUENCE 3

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
    void exit();


	void keyPressed  (int key);
	void keyReleased(int key);
    void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
    void drawDebug(bool);

    
    //--------
    
    void choseRandomNote();
    void assignNoteToPlayer();
    void loadSequence();
    void playSequence();
    void togglePlay();
    void saveLog();
    float difficulty();

    
    void defineButton(int);     //according to who pushes define if button is higher or lower.
    void checkPushedButton (Button up, Button down);
    void activateButton(Button &b, bool val);
    void setupXML();
    
    void checkNote();
    void checkPreviousNote();
    
    void emptySequence();
    void drawPulse(float, float, int);
    
    void resetPulse();
    void loadInstrument();
    
    
    Button leftButt;
    Button  rightButt;
    Button playSeq;
    Button playAgain;
    
    //array containing
    int noteIndex[NUM_TONES];
    int previousNote;   //previously played note
    
    ofDirectory dir;
    vector <string> folderName;
        
    bool bFlagNote;
    bool bGameover, bWin;
    bool bButtonsActive;
    bool bPlaySeq;
    bool bLoadSeq;
    bool bDebug;
    bool bIncreasingDifficulty;


    vector <ofSoundPlayer> player;
    vector<int>randomSequence;
    vector<bool>pressedSequence; //this is the sequence storing the bools of the pressed buttons
    vector<bool>realSequence;    //this stores the bools of the real sequence to compare with pressedSequence
    
    int counter, playerCounter, playAgainCounter, gameCounter;
    string path;
    
    WriteFile log;
    ofXml settings;
    char leftKey, rightKey, playAgainKey;
    string playKey;
    
    ofImage bg, fail;
    ofVideoPlayer winVideo;
    
    
};
