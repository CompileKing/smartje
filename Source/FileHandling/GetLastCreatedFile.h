/*
  ==============================================================================

    GetLastCreatedFile.h
    Created: 19 Nov 2019 4:48:23pm
    Author:  Sem Shimla

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
#include <vector>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort
using namespace std;

class FileHandler
{
public:
    FileHandler();
    ~FileHandler();
    File getLastCreatedFile();
    
        
private:
    int stdSorter();
    int fillFileArrayFromDocuments();
    void debugFileArrays(string fileIndex, string relativeTimeDouble);
    void debugFileArrays(string fileName, string fileIndex, string relativeTimeDouble);
    Array<File> importedFiles;
    File fileFromMailClient;
    std::vector<float> myVector;
    std::vector<int> mySortedVector;
};
