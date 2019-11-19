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
    int numberOfFiles = fillFileArrayFromDocuments();
    for (int i = 0; i < numberOfFiles; i++)
    {
        RelativeTime relativeFileTime =
        Time::getCurrentTime() - importedFiles.getReference(i).getCreationTime();
        dateCreatedArray.add(relativeFileTime);
        myVector[i] = relativeFileTime.inSeconds();
        
        debugFileArrays(importedFiles.getReference(i).getFileName().toStdString(),
                        to_string(i),
                        to_string(relativeFileTime.inSeconds()));
    }
            
    Array<RelativeTime> dateCreatedArrayUnsorted = dateCreatedArray;
    dateCreatedArray.sort(sorter);
    int indexOfLastCreatedFile = dateCreatedArray.indexOfSorted(sorter, dateCreatedArray.getFirst());
    
    cout << endl;
    cout << "================================" << endl;
    for (int i = 0; i < dateCreatedArray.size(); i++)
    {
        cout << endl <<
        "new sorted index:    " << to_string(i) << endl <<
        "relative timeStamp: " << to_string(dateCreatedArray.getReference(i).inSeconds()) << endl;
    }
    cout << endl <<
    "indexOfLastCreatedFile: " << indexOfLastCreatedFile << endl;
    
    fileFromMailClient = importedFiles.getReference(indexOfLastCreatedFile);
    return fileFromMailClient;

//    String firstFile = importedFiles.getFirst().getFileName() +
//    " // numberOfFiles: " + to_string(numberOfFiles) +
//    " // indexOfSorted: " + to_string(indexOfLastCreatedFile) +
//    " // fileFromSorted:" + fileFromMailClient.getFileName();
//    fileFromMailClientLabel.setText(firstFile,dontSendNotification);
}


int FileHandler::stdSorter()
{
    for (auto i: sort_indexes(myVector))
    {
        cout << myVector[i] << endl;
    }
}

int FileHandler::fillFileArrayFromDocuments()
{
    // clear all the arrays and vectors
    for (auto i: myVector)
        myVector[i] = 0.f;
    importedFiles.clear();
    dateCreatedArray.clear();
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
    
//    cout << endl <<
//    "fileName: " << importedFiles.getReference(i).getFileName() << endl <<
//    "original file index: " << to_string(i) << endl <<
//    "relativeTimeDouble: " << to_string(relativeFileTime.inSeconds()) << endl;
}


