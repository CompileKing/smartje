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
    
    
    int compResX;
    int compResY;
    
    int vIndex = 0;
    int vIndexOut = 0;
    int sIndex = 0;
    int sliceIndex = 0;
    int screenIndex = 0;
    
    int sliceEnabledArray[10000];
    int screenIndexArray[8];
    String screenNameArray[8];
    String sliceNameArray[10000];
    String sliceName;
    
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
    
    bool isFileLoaded;
    
    bool result2;
    
    
    
    
    
    
    
};












#endif /* InputRect_hpp */

