//
//  rotateBass.h
//  box2d_UGen_Leap
//
//  Created by 諸岡 光男 on 2013/11/02.
//
//
#pragma once

#include "ofxUGen.h"

class rotateBass : public ofxUGen::SynthDef
{
public:
   	
	UGen envgen;
	UGen amp;
    
    float volume,count;
    
    ofVec3f pos ;
    ofVec2f enMove1,enMove2,enMove3;
    
    rotateBass(int x,int y,int z,int freq1,int freq2,bool choice,int volume2)
    {
        pos.x = x;
        pos.y = y;
        pos.z = z;
        
        float freq = ofMap(pos.y,0, ofGetHeight(), freq1,freq2);      //80, 400
        float pan = ofMap(pos.x, 0,ofGetWidth(), -1, 1);
        float volume = ofMap(pos.z,50, 700, 200, 1);
        
		Env env = Env::perc(0.3, 0.3, 0.5, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
        if(choice) amp = SinOsc::AR(ofRandom(4.0), 0, 0.3, 0.3) * envgen;
        else amp = SinOsc::AR(ofRandom(4.0), 0, 0.3, 0.3);
		
		Out(
			Pan2::AR(SinOsc::AR(freq) * amp * volume/volume2, pan)      //volume2 = 100
            );
    }
    
    void draw(){
        count = count + 0.2f*amp.getValue()*10;
        
        enMove1.x = std::cos(count)*500*amp.getValue();
        enMove1.y = std::sin(count)*500*amp.getValue();
        
        enMove2.x = std::cos(count+600)*500*amp.getValue();
        enMove2.y = std::sin(count+600)*500*amp.getValue();
        
        ofFill();
		ofSetColor(110,29,56,1000*amp.getValue());
        ofTriangle(pos.x+enMove1.x,pos.y+enMove1.y-15,pos.x+enMove1.x-150*amp.getValue(),pos.y+enMove1.y+150*amp.getValue(),
                   pos.x+enMove1.x+150*amp.getValue(),pos.y+enMove1.y+150*amp.getValue());
        ofSetColor(226,82,77,1000*amp.getValue());
        ofTriangle(pos.x+enMove2.x,pos.y+enMove2.y-15,pos.x+enMove2.x-150*amp.getValue(),pos.y+enMove2.y+150*amp.getValue(),
                   pos.x+enMove2.x+150*amp.getValue(),pos.y+enMove2.y+150*amp.getValue());
    }
    void draw2(int x,int y,int z){
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        ofBackground(x,y,z);
    }
    
    bool isAlive()
	{
		return !Out().isNull();
	}
	
};
