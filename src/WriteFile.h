#pragma once

#include "ofMain.h"


class WriteFile {
public:
    void setup(string name);
    void update(string description, string data);
    void saveFile();
    
    int folder;
    string path;
    
    ofBuffer buffer;
    ofFile log;
    
    
    
};
