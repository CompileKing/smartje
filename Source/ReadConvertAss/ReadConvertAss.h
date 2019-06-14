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


using namespace std;


class InputRect
{
private:
    
    
    
    
    
public:
    
    string assPath;
    int compResX;
    int compResY;
    
    int vIndex = 0;
    int sIndex = 0;
    
    void getInputRect();
    
    double xArray[1000];
    double *xArrayPtr = xArray;
    
    double yArray[1000];
    double *yArrayPtr = yArray;
    
    bool isFileLoaded;
    
    bool result1;
    bool result2;
    
    
    
    
    
};












#endif /* InputRect_hpp */

