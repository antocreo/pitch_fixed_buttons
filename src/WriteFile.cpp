#include "WriteFile.h"

WriteFile::WriteFile(){};

//--------------------------------------------------------------
void WriteFile::setup(string name){
    
    path = "logs/" + ofToString(ofGetDay()) +"_"+ ofToString(ofGetHours())+"_"+ ofToString(ofGetMinutes())+"_"+ ofToString(ofGetSeconds());


    //create the folder if doens't exist already
    
        buffer.begin();
        log.open(path +"/"+ name + ".txt", ofFile::Append);
    
    
}

//--------------------------------------------------------------
void WriteFile::update(string description, string data){
    
     buffer.append(description + data + "\n");


}


//--------------------------------------------------------------
void WriteFile::saveFile(){
    

    //no data gets saved unless you hit the s key
    
        //create dir if doesn't exist
        ofDirectory dir(path);
        if(!dir.exists()){
            dir.create(true);
        }
    
    log.writeFromBuffer(buffer);

}
