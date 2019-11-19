/*
  ==============================================================================

    GetLastCreatedFile.cpp
    Created: 19 Nov 2019 4:48:23pm
    Author:  Sem Shimla

  ==============================================================================
*/

#include "GetLastCreatedFile.h"


FileHandler::FileHandler()
{
    
}
FileHandler::~FileHandler()
{
    
}

template <typename T>
vector<size_t> sort_indexes(const vector<T> &v) {
    
    // initialize original index locations
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);
    
    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(),
         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
    
    return idx;
}

File FileHandler::getLastCreatedFile()
{
    // get array of files and vector with relative creation times
    int numberOfFiles = fillFileArrayFromDocuments();
    for (int i = 0; i < numberOfFiles; i++)
    {
        RelativeTime relativeFileTime =
           importedFiles.getReference(i).getLastAccessTime() - Time::getCurrentTime()  ;
        myVector.push_back(relativeFileTime.inSeconds());
        debugFileArrays(importedFiles.getReference(i).getFileName().toStdString(),
                        to_string(i),
                        to_string(relativeFileTime.inSeconds()));
    }
    cout << endl << "=========================" << endl << endl;
    stdSorter();
    fileFromMailClient = importedFiles.getReference(mySortedVector[0]);
    return fileFromMailClient;
}


int FileHandler::stdSorter()
{
    for (auto i: sort_indexes(myVector))
    {
        cout << "after sort: " << myVector[i] << endl;
        cout << "sortIndex: " << to_string(i) << endl;        
        mySortedVector.push_back(i);
    }
    return 1;
}

int FileHandler::fillFileArrayFromDocuments()
{
    // clear all the arrays and vectors
    myVector.clear();
    mySortedVector.clear();
    importedFiles.clear();
    // find files, store them in the importedFiles array and return number of files found
    bool searchRecursively = true;
    String wildCardPattern = "*.xml";
    int numberOfFiles = File::getSpecialLocation(File::userDocumentsDirectory).findChildFiles(importedFiles, File::findFiles, searchRecursively, wildCardPattern);
    return numberOfFiles;
}

void FileHandler::debugFileArrays(string fileIndex, string relativeTimeDouble)
{
    cout << endl <<
    "original file index: " << fileIndex << endl <<
    "relativeTimeDouble: " << relativeTimeDouble << endl;
}
void FileHandler::debugFileArrays(string fileName, string fileIndex, string relativeTimeDouble)
{
    cout << endl <<
    "fileName: " << fileName << endl <<
    "original file index: " << fileIndex << endl <<
    "relativeTimeDouble: " << relativeTimeDouble << endl;
}


