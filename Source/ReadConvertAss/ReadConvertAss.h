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
    int screenIndexArray[10000]; // shows how many slices there are per screen
    int screenWidthArray[10000];
    int screenHeightArray[10000];
    
    String screenNameArray[10000]; // names of all of the screens
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
    
    float xArrayRaw[10000];
    float yArrayRaw[10000];
    float xArrayOutRaw[10000];
    float yArrayOutRaw[10000];
    
    float inputSliceRotationArray[10000];
    float outputSliceRotationArray[10000];
    
    
    bool isFileLoaded;
    bool result2;
    bool isAss;
    bool isXml;

};

#endif /* InputRect_hpp */

