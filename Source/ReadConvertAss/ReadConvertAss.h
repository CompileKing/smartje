/*
  ==============================================================================

    ReadConvertAss.h
    Created: 14 Jun 2019 5:29:04pm
    Author:  Sem Shimla

  ==============================================================================
*/

#pragma once
#ifndef InputRect_hpp
#define InputRect_hpp

#include <stdio.h>
#include "../Pugi/pugixml.hpp"
#include <iostream>
#include <string>
#include "../JuceLibraryCode/JuceHeader.h"


using namespace std;


class InputRect : public Component
{
private:

public:
    
    
    float compResX;
    float compResY;
    float aspectRatioInput;
        
    float screenResX;
    float screenResY;
    
    int vIndex = 0;
    int vIndexOut = 0;
    int sIndex = 0;
    int sliceIndex = 0;
    int screenIndex = 0;
    
    int sliceEnabledArray[10000]; //tells which slices are enabled
    int screenIndexArray[100]; // shows how many slices there are per screen
    int screenWidthArray[100];
    int screenHeightArray[100];
    
    String screenNameArray[100]; // names of all of the screens
    String sliceNameArray[10000]; //names of all the slices
    String sliceName; //slice name variable
    
    int sliceX;
    int sliceY;
    int sliceXarray[10000];
    int sliceYarray[10000];
    
    void getInputRect(std::string assFile);
    
    float xArray[10000];
    float *xArrayPtr = xArray;
    
    float yArray[10000];
    float *yArrayPtr = yArray;
    
    float xArrayOut[10000];
    float *xArrayOutPtr = xArrayOut;
    
    float yArrayOut[10000];
    float *yArrayOutPtr = yArrayOut;
    
    float xArrayRaw[1000];
    float yArrayRaw[1000];
    float xArrayOutRaw[1000];
    float yArrayOutRaw[1000];
    
    float inputSliceRotationArray[1000];
    float outputSliceRotationArray[1000];
    
    
    bool isFileLoaded;
    
    bool result2;
    
    bool olderResVersionDetected;

};

#endif /* InputRect_hpp */

