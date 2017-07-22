#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetCircleResolution(60);
    ofBackground(200);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetBackgroundAuto(true);

    bg.load("images/bg.png");
    
    //loading buttons
    leftButt.loadFont("ArialBold.ttf", 20);
    rightButt.loadFont("ArialBold.ttf", 20);
    playSeq.loadFont("ArialBold.ttf", 20);
    playAgain.loadFont("ArialBold.ttf", 20);
    
    //setting colors standby for the buttons
    leftButt.setButtColor(150, 30, 10, 100);
    rightButt.setButtColor(150, 30, 10, 100);
    playAgain.setButtColor(150, 30, 10, 100);
    
    //setting labels
    leftButtLabel = "DOWN";
    rightButtLabel = "UP";
    
    //  //load all the files in the players
    dir.listDir("tones");
    for (int i = 0; i <(int) dir.size(); i++) {
        player.push_back(*new ofSoundPlayer);
        player[i].load(dir.getPath(i), true);
    }
    

    
    bDebug = false;
    bGameover = false;
    bWin = false;
    bPlaySeq = false;
    bButtonsActive = false; //let's start with left and right buttons not active
    bLoadSeq = false;
    
    setupXML();
    
    playerCounter = 0;
    playAgainCounter = 0;
    gameCounter = 0;
    
    //load random sequence
    loadSequence();
    
    //saving the file
    log.setup("log");
    
    //load winVideo
    winVideo.load("video/win.mov");
//    winVideo.setLoopState(OF_LOOP_NONE);

    //load image from fail
    fail.load("images/fail.png");
}

//--------------------------------------------------------------
void ofApp::update() {
    
    ofSoundUpdate();
    //update buttons only for the animation pulse.
    leftButt.update(1, player[randomSequence[pressedSequence.size()-1]], 1);
    rightButt.update(1, player[randomSequence[pressedSequence.size()-1]], 1);
    playSeq.update(1, player[randomSequence[playerCounter]], 1);
    
    //PLAY BUTTON
    //check the button is toggled and that the players and the sequence is filled
    //when the sequence has finished just reset
    if (playSeq.getbActive()) {
        if (bLoadSeq && !player[randomSequence[playerCounter]].isPlaying()){
            playSequence();
            playSeq.setbPulse(true);
        }
        else if (bLoadSeq && !playSeq.getbActive()) {
            emptySequence();
            playSeq.setbPulse(false);
        }
    }
    
    //when the sequence has finished just RESET
    if (playerCounter == counter - 1 && !player[randomSequence[playerCounter]].isPlaying()) {
        bButtonsActive = true; //activate L & R buttons
        leftButt.setButtColor(150, 30, 10);
        rightButt.setButtColor(150, 30, 10);
        playAgain.setButtColor(150, 30, 10);
        
    }
    
    
    //UP AND DOWN BUTTON
    //let's start with the game
    //let's check the first button pressed (pressedSeq is empty) and assign the first value as true (like in the realSequence)
    
    //deactivate the buttons again if you press x counter times.
    if (pressedSequence.size() >= realSequence.size() && !player[randomSequence[playerCounter]].isPlaying()) {
        bButtonsActive = false;
    }
    
    if (!bButtonsActive) {
        //setting colors standby for the buttons
        leftButt.setButtColor(150, 30, 10, 100);
        rightButt.setButtColor(150, 30, 10, 100);
        playAgain.setButtColor(150, 30, 10, 100);
    }
    
    //WIN OR LOSE
    //let's check if the sequence is the same
    //checking the size
    if (pressedSequence.size() > 0 && pressedSequence.size() == realSequence.size() && !player[randomSequence[playerCounter]].isPlaying()) {
        
        bGameover = true;
        
        //compare the 2 vectors
        if (pressedSequence == realSequence) {
            
            bWin = true;
            
        } else !bWin;
    }
    
    
    //update the video
    if (bGameover && !player[randomSequence[playerCounter]].isPlaying()) {
        if (bWin) {
            winVideo.play();
            winVideo.update();
        }
    }
    


    
}

//--------------------------------------------------------------
void ofApp::draw() {


    bg.draw(0, 0, ofGetWidth(), ofGetHeight());
    
//    ofDrawBitmapString(ofToString(bPulse), 10, 10);
//    ofDrawBitmapString(ofToString(pressedSequence.size()-1), 10, 20);
//    
    
    
    float playW = 400;
    float plAgW = playW/2;
    float playX = (ofGetWidth() - playW)/2;
    float playY = (ofGetHeight() - playW)/2;
    float margin = 30 ;
    
    if (!bGameover){
        
        if (!bButtonsActive && pressedSequence.size() == 0) {
            ofPushStyle();
            //PLAY
            if(!playSeq.getbActive()) {
                playSeq.draw(playX, playY, playW, playW, "play_standby.png");
            } else playSeq.draw(playX, playY, playW, playW, "play_active.png");
            
            ofPopStyle();
        }
       

        if (bButtonsActive) {
            //draw buttons

            //LEFT/DOWN
            ofPushStyle();
            if(!leftButt.getbActive()) {
                leftButt.draw(margin, playY, playW, playW, "down_standby.png");
            } else leftButt.draw(margin, playY, playW, playW, "down_active.png");
            ofPopStyle();
            
            //RIGHT/UP
            ofPushStyle();
            if(!rightButt.getbActive()) {
                rightButt.draw(ofGetWidth() - margin - playW, playY, playW, playW, "up_standby.png");
            } else  rightButt.draw(ofGetWidth() - margin - playW, playY, playW, playW, "up_active.png");
            
            ofPopStyle();

            //PLAY AGAIN
            ofPushStyle();
            if(!playAgain.getbActive()) {
                playAgain.draw((ofGetWidth() - plAgW)/2, ofGetHeight() - plAgW - margin, plAgW, plAgW, "play_standby.png");
            } else     playAgain.draw((ofGetWidth() - plAgW)/2, ofGetHeight() - plAgW - margin, plAgW, plAgW, "play_standby.png");
            
            ofPopStyle();
            
            //just drawing lines to get the center.
//            ofDrawLine(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);
//            ofDrawLine(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
            
            //drawing DOTS
            
            float dotSize = 15 * 2;
            float dotDist = 5;
            float central  = (ofGetHeight() - (dotSize + dotDist) * realSequence.size())/2;
            
            //translating just the dots
            ofPushMatrix();
            ofTranslate(0, -central - dotSize);
            
            //draw the empty ones
            for (int i = 0; i<realSequence.size(); i++) {
            ofPushStyle();
            ofNoFill();
            ofSetColor(255, 255, 255);
            ofDrawCircle(ofGetWidth()/2, ofGetHeight() - (dotSize + dotDist) * i, dotSize/2 -2);
            ofPopStyle();
            }

            //draw the pressed ones
            for (int i = 0; i<pressedSequence.size(); i++) {

                if (pressedSequence[i] != realSequence[i]) {
                    ofPushStyle();
                    ofFill();
                    ofSetColor(200, 0, 0);
                    ofDrawCircle(ofGetWidth()/2, ofGetHeight() - (dotSize + dotDist) * i, dotSize/2);
                    ofPopStyle();

                } else {
                    
                    ofPushStyle();
                    ofFill();
                    ofSetColor(0, 200, 0);
                    ofDrawCircle(ofGetWidth()/2, ofGetHeight() - (dotSize + dotDist) * i, dotSize/2);
                    ofPopStyle();
                    
                }
                
            }
            ofPopMatrix(); //end translation of the dots

        }
       
    }
    
    //drawing debug overlayed //leave it at the bottom
    drawDebug(bDebug);
    
    if (bGameover && !player[randomSequence[playerCounter]].isPlaying()) {
        string message;
        if (bWin) {
            ofPushStyle();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
            winVideo.draw(ofGetWidth()/2, ofGetHeight()/2, winVideo.getWidth(), winVideo.getHeight());
            ofDisableBlendMode();
            ofPopStyle();
        } else {
            ofPushStyle();
            ofSetRectMode(OF_RECTMODE_CENTER);
            fail.draw(ofGetWidth()/2, ofGetHeight()/2, fail.getWidth(), fail.getHeight());
            ofPopStyle();
        }
//        ofTrueTypeFont winMessage;
//        winMessage.load("ArialBold.ttf", 100);
//        winMessage.drawString(message, (ofGetWidth() - winMessage.stringWidth(message))/2, (ofGetHeight()/2) );
//        winMessage.load("ArialBold.ttf", 20);
//        winMessage.drawString("press " + playKey, (ofGetWidth() - winMessage.stringWidth("press " + playKey ))/2, (ofGetHeight()/2 + 40) );
        
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    
    if (key == leftKey){
        if (bButtonsActive) {
            leftButt.setbActive(true);
            resetPulse();

        }
    }
    
    if (key == rightKey) {
        if (bButtonsActive) {
            rightButt.setbActive(true);
            resetPulse();

        }
    }
    
    if (key == ofToChar(playKey)) {
        
        resetPulse();
        
    }
    
    if (key == playAgainKey) {
        if (bButtonsActive) {
            playAgain.setbActive(!playAgain.getbActive());
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
    
    if (key == leftKey) {
   
       /* 
        if (bButtonsActive) {
            
            leftButt.setbActive(false);
            
            //control the sequence insertion
            leftButt.setbPitch(false);

            pressedSequence.push_back(leftButt.getbPitch());
            player[randomSequence[pressedSequence.size()-1]].play();
            
        }
        */
        activateButton(leftButt, false);
        

    }
    
    if (key == rightKey) {
        /*
        if (bButtonsActive) {
            
            rightButt.setbActive(false);
            
            //control the sequence insertion
            rightButt.setbPitch(true);

            pressedSequence.push_back(rightButt.getbPitch());
            player[randomSequence[pressedSequence.size()-1]].play();
            
        }
        */
        activateButton(rightButt, true);
        
    }
    
    //play button is a toggle
    if (!bButtonsActive && key == ofToChar(playKey) ) {
        togglePlay();
    }
    
    if (key == playAgainKey) {
        if (bButtonsActive) {
            playAgain.setbActive(!playAgain.getbActive());
            playAgainCounter++; // for log stats
            playerCounter = 0;
            player[randomSequence[playerCounter]].play();
        }
    }
    
    
    
    
    if (key == 'd') {
        bDebug = !bDebug;
    }
}



//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
    //LEFT BUTTON
    if (leftButt.getRectangle().inside(x, y)) {
        if (bButtonsActive) {
            leftButt.setbActive(true);
            resetPulse();
        }
    }
    //RIGHT BUTTON
    if (rightButt.getRectangle().inside(x, y)) {
        if (bButtonsActive) {
            rightButt.setbActive(true);
            resetPulse();
        }
    }
    
    //PLAY BUTTON
    if (playSeq.getRectangle().inside(x, y)) {
        if (bButtonsActive) {
            playSeq.setbActive(!playSeq.getbActive());
            resetPulse();
        }
        
    }

    
    //PLAY AGAIN BUTTON
    if (playAgain.getRectangle().inside(x, y)) {
        if (bButtonsActive) {
            playAgain.setbActive(!playAgain.getbActive());
            resetPulse();
        }

    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    //LEFT BUTTON
    if (leftButt.getRectangle().inside(x, y)) {
        activateButton(leftButt, false);
    }
    
    //RIGHT BUTTON
    if (rightButt.getRectangle().inside(x, y)) {
        activateButton(rightButt, true);
    }
    
    
    //PLAY BUTTON
    if (!bButtonsActive && playSeq.getRectangle().inside(x, y)) {
        togglePlay();
    }
    
    
    //PLAY AGAIN BUTTON
    if (playAgain.getRectangle().inside(x, y)) {
        if (bButtonsActive) {
            playAgain.setbActive(!playAgain.getbActive());
            playAgainCounter++; // for log stats
            playerCounter = 0;
            player[randomSequence[playerCounter]].play();
        }
    }
}



//--------------------------------------------------------------

void ofApp::loadSequence(){
    
    //if the buttons are active, deactivate them then load the sequence
    if (bButtonsActive) {
        bButtonsActive = false;
    }
    
    //CREATE THE RANDOM SEQUENCE
    //creates a vector of "counter" size with random number. there are not equal adjacent numbers
    //iterate for num of notes in the sequence
    for (int i = 0; i < counter; i++) {
        
        //check the vector size is < of counter size
        if (randomSequence.size() < counter) {
            
            //create random number from 0 to 13
            int randNote =int(ofRandom(0, NUM_TONES-1));
            
            //then, check if the vector is empty
            if (randomSequence.empty()) {
                //push this number in the vector
                randomSequence.push_back(randNote);
                //push true in the real sequence. the first number will be always 1
                realSequence.push_back(true);
            } else {
                //check new number is different from last one
                if (randNote != randomSequence[randomSequence.size()-1]) {
                    
                    //check if it's higher or lower
                    if (randNote > randomSequence[randomSequence.size()-1]) {
                        //push this number in the vector
                        randomSequence.push_back(randNote);
                        //push value in the seq
                        realSequence.push_back(true);
                        
                    } else if (randNote < randomSequence[randomSequence.size()-1]) {
                        //push this number in the vector
                        randomSequence.push_back(randNote);
                        //push value in the seq
                        realSequence.push_back(false);
                    }
                    
                    //if adjacents are equal chose another random note
                } else randNote = int(ofRandom(0, NUM_TONES-1));
            }
        }
    }
 
    // adjust the first dude THE CORRECT SEQUENCE OF BOOLEANS
    if (randomSequence.size() > 0 && randomSequence.size() == counter) {
        
        if (randomSequence[1] > randomSequence[0]) {
            realSequence[0] = false;
        }
    }

    
    //CHECKING AND LOADING
    
    if (randomSequence.size() == counter && realSequence.size() == counter) {
        bLoadSeq = true;
        gameCounter++;
        
    } else loadSequence();
    
    
}

//--------------------------------------------------------------

void ofApp::playSequence(){
    //this function runs in the update loop so that the file can play
    
    //check vector size
    if (player.size() > 0 && randomSequence.size() > 0) {
        if (playerCounter < counter - 1){
            playerCounter++;
            player[randomSequence[playerCounter]].play();
        }
    }
}


//--------------------------------------------------------------

void ofApp::emptySequence(){
    
    //comment this if block if you don't want to get the increasing level of difficulty
    //or just deacrivate via XML settings
    if (bWin && bIncreasingDifficulty ) {
        counter++;
    }
    // end of level difficulty
    
    bLoadSeq = false;
    
    //check if it's not empty
    if (!randomSequence.empty()) {
        randomSequence.clear();
        realSequence.clear();
        pressedSequence.clear();
        
        player[randomSequence[playerCounter]].stop();
        winVideo.stop();
        bGameover = false;
        bWin = false;
        playAgainCounter = 0;
        
        //reset the pulse on the buttons
        leftButt.setbPulse(false);
        rightButt.setbPulse(false);
        playSeq.setbPulse(false);
        
    }
    
    playerCounter = 0;
    
}


//--------------------------------------------------------------

void ofApp::togglePlay(){
    
    //this function runs just at the mouse/key event and plays the 1st file
    
    playSeq.setbActive(!playSeq.getbActive());
    
    if (playSeq.getbActive()) {
        
        if (!bLoadSeq) {
            loadSequence();
        }
        
        if (player.size() > 0 && randomSequence.size() > 0) {
            if (playerCounter < counter - 1){
                player[randomSequence[playerCounter]].play();
                playSeq.setbPulse(true);

            }
        }
        
    } else if (!playSeq.getbActive()) {
        //        if (bLoadSeq) {
        saveLog();
        //        }
        emptySequence();
    }
}

//--------------------------------------------------------------

void ofApp::checkPushedButton (Button first, Button second){
    
    if (pressedSequence.size() < realSequence.size()){
        
        if (pressedSequence.empty() ) {
            first.setbPitch(true);
            second.setbPitch(false);
            //whatever button will be pressed at the beginning it will always be true;
            pressedSequence.push_back(first.getbPitch());
        }
        //if it's not empty push into the pressedSeq whatever is the temporary label of the button
        else {
            pressedSequence.push_back(first.getbPitch());
        }
    }
}


//--------------------------------------------------------------


void ofApp::drawDebug(bool b){
    
    if (b) {
        
        ofPushStyle();
        ofSetColor(0, 0, 0,190);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()/4);
        ofPopStyle();
        
        ofDrawBitmapString("PlayAct + buttAct + bWin " + ofToString(playSeq.getbActive()) + " " + ofToString(bButtonsActive) + " " + ofToString(bWin), 20, 20);
        ofDrawBitmapString("RealSeq Size " + ofToString(realSequence.size()), 20, 40);
        ofDrawBitmapString("PressedSeq Size " + ofToString(pressedSequence.size()), 20, 60);
        ofDrawBitmapString("SEQ SIZE " + ofToString(randomSequence.size()), 20, 80);
        ofDrawBitmapString("PLAYER SIZE " + ofToString(player.size()), 20, 100);
        ofDrawBitmapString("PLAYERCOUNTER " + ofToString(playerCounter), 20, 140);
        ofDrawBitmapString("COUNTER " + ofToString(counter), 20, 160);
        if (playerCounter>0) {
            ofDrawBitmapString("is playing? " + ofToString(player[randomSequence[playerCounter]].isPlaying()), 20, 180);
        }
        ofDrawBitmapString("upBut + downBut " + ofToString(rightButt.getbPitch()) + " " + ofToString(leftButt.getbPitch()), 20, 200);
        ofDrawBitmapString("DIFFICULTY " + ofToString(difficulty()), 670, 20);
        
        
        for (int i = 0; i < realSequence.size(); i++) {
            ofDrawBitmapString("realSeq " + ofToString(realSequence[i]), 320, 20 + 20*i);
            
        }
        
        for (int i = 0; i < pressedSequence.size(); i++) {
            ofDrawBitmapString("pressedseq " + ofToString(pressedSequence[i]), 440, 20 + 20*i);
            
        }
        
        if (randomSequence.size() > 0) {
            
            for (int i = 0; i < counter; i++) {
                ofDrawBitmapString("SEQ " + ofToString(randomSequence[i]), 570, 20 + 20*i);
                if (playerCounter>0) {
                    ofDrawBitmapString("RANDOM SEQ INDEX " + ofToString(randomSequence[playerCounter]), 20, 120);
                }
            }
        }
        
    }
}

//--------------------------------------------------------------


void ofApp::saveLog(){
    
    //update and write file
    log.update("Game num: ", ofToString(gameCounter));
    log.update("Sequence of: ", ofToString(counter));
    log.update("Difficulty: ", ofToString(difficulty()));
    log.update("Repeated num of time: ", ofToString(playAgainCounter));
    
    
    log.update("-------", "--------- \n");
    
    if (randomSequence.size() > 0) {
        for (int i = 0; i < randomSequence.size(); i++) {
            log.update("Notes Sequence ", ofToString(randomSequence[i]));
        }
        log.update("-------", "--------- \n");
    }
    if (realSequence.size() > 0) {
        for (int i = 0; i < realSequence.size(); i++) {
            log.update("Winning Sequence ", ofToString(realSequence[i]));
        }
        log.update("-------", "--------- \n");
    }
    if (pressedSequence.size() > 0) {
        
        for (int i = 0; i < pressedSequence.size(); i++) {
            log.update("Pressed Sequence ", ofToString(pressedSequence[i]));
        }
        log.update("-------", "--------- \n");
    }
    
    if (bWin) {
        log.update("Game ", "Won");
    } else if (!bWin){
        log.update("Game ", "Lost");
    }
    log.update("-------", "--------- \n");
    
    
}

//--------------------------------------------------------------

void ofApp::exit(){
    log.saveFile();
}

//--------------------------------------------------------------

float ofApp::difficulty(){
    /*what are we doing here? we define the level of difficulty
     by calculating the note distance for each interval. The shorter the distance the more difficult
     so we iterate trhough the vector and calculate the abs difference between the elements, then divide for the num
     of time we calculated and the we subtract that result from the num of notes available
     */
    
    int divider = 0;
    float tempDiff = 0;
    for (int i = 0; i < randomSequence.size(); i++) {
        if (i<randomSequence.size()-1) {
            tempDiff += abs (randomSequence[i+1] - randomSequence[i]) ;
            divider++;
        }
    }
    
    return abs (floor((NUM_TONES) - ( tempDiff / divider )) );
}

//--------------------------------------------------------------


void ofApp::activateButton(Button &b, bool val){

    if (bButtonsActive) {
        
        b.setbActive(false);
    
        //control the sequence insertion
        b.setbPitch(val);

        if (pressedSequence.size() < realSequence.size()) {
            pressedSequence.push_back(b.getbPitch());
            player[randomSequence[pressedSequence.size()-1]].play();
        }
       
        if (pressedSequence[pressedSequence.size()-1] == realSequence[pressedSequence.size()-1]) {
            b.setbPulse(true);
        } else {
            b.setbPulse(false);
        }
    }
    
   }

//--------------------------------------------------------------

void ofApp::setupXML(){

    //XML settings
    //load the xml
    settings.load("settings.xml");
    
    //increasing difficulty set the variable
    if(settings.exists("//increasingDifficulty")) {
        bIncreasingDifficulty	= settings.getValue<int>("//increasingDifficulty");
    } else{
        bIncreasingDifficulty = true;   //default is true
    }
    
    //check if it exists, then set the commands
    if(settings.exists("//sequence")) {
        counter	= settings.getValue<int>("//sequence");
    } else{
        counter = MAX_SEQUENCE;    //we start with a sequence of 3 - this keeps the value of num of notes in the sequence
    }
    if(settings.exists("//leftButton")) {
        leftKey = settings.getValue<char>("//leftButton");
    } else{
        leftKey = 'a';
    }
    if(settings.exists("//rightButton")) {
        rightKey = settings.getValue<char>("//rightButton");
    } else {
        rightKey = 'l';
    }
    
    if(settings.exists("//playButton") && !settings.getValue<string>("//playButton").empty()) {
        playKey = settings.getValue<string>("//playButton");
    } else {
        playKey = ' ';
    }
    
    if(settings.exists("//playAgainButton")) {
        playAgainKey = settings.getValue<char>("//playAgainButton");
    } else {
        playAgainKey = 'r';
    }

}

void ofApp::resetPulse(){

    leftButt.setbPulse(false);
    leftButt.getButtonPulse()->increment = 0;
    rightButt.setbPulse(false);
    rightButt.getButtonPulse()->increment = 0;
    playSeq.setbPulse(false);
    
}

