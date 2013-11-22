//
//  myHarmonicOsc.h
//  box2d_UGen_Leap
//
//  Created by 諸岡 光男 on 2013/11/02.
//
//
#pragma once

#include "ofxUGen.h"

class myHarmonicOsc : public ofxUGen::SynthDef
{
public:
	
	ofVec3f pos;
	
	UGen envgen;
	UGen amp;
    
	myHarmonicOsc(int x,int y,int z,bool choise)
	{
		pos.x = x;
		pos.y = y;
        pos.z = z;
		
		float freq = ofMap(pos.y, 0, ofGetHeight(), 50, 150);
		float pan = ofMap(pos.x, 0, ofGetWidth(), -1, 1);
        float volume = ofMap(pos.z,50, 700, 300, 1);
        
		Env env = Env::perc(0.6, 0.5, 0.5, EnvCurve::Welch);  //sine // Numerical :Welch
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
        if (choise) {
            amp = SinOsc() * envgen;    //0, 0, 0.5, 0.5
        }else amp = LFPulse::AR() * envgen;
        
        Out(
            //  Pan2::AR(SinOsc::AR(freq)*amp*delay, pan)
            Pan2::AR(HarmonicOsc::AR(Buffer(1.0, 0.5, 0.333, 0.25, 0.2, 0.167, 0.143, 0.125),freq)*amp*volume/500, pan)
            );
    }
    
    void draw(int x,int y,int z, int s)
	{
        ofLine(x,y,z,s);
    }
    
};
