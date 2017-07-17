#pragma once

#include "ofMain.h"

class ButtonPulse {
	public:
		void setup();
		void update(int speedModulo, ofSoundPlayer &player, float incrementVariation);
		void draw(float x, float y);
        void drawPlay(float x, float y);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    
    float increment;
};
