/*
  ==============================================================================

    ReadConvertAss.cpp
    Created: 14 Jun 2019 5:29:04pm
    Author:  Sem Shimla

  ==============================================================================
*/

#include "ReadConvertAss.h"

#ifdef _WIN64

#include <Windows.h>
#include <ShlObj.h>

#endif


//=====================================================================================
//                       get the ASS path from the preferences file
//=====================================================================================




void InputRect::getInputRect(std::string assFile)
{
    
    //=====================================================================================
    //                       retrieved ASS PATH as string assPath
    //=====================================================================================
    
    
    cout << endl;
    cout << endl;
    cout << "/////////////////////////////////////PUGI/////////////////////////////////////" <<endl;
    cout << endl;
    cout << "pugi from param: " << assFile << endl;
    
    vIndex = 0;
    sIndex = 0;

    pugi::xml_document doc;
    pugi::xml_parse_result
    result2 = doc.load_file(assFile.c_str());
    
    cout << "pugi is loaded? " << result2 << endl;
    cout << "Load result: " << result2.description() << endl;
    
    cout << endl;
    cout << "//////////////////////////////////////////////////////////////////////////////" <<endl;
    cout << endl;
    cout << endl;
    
    
    
    compResX = doc.child("XmlState").child("ScreenSetup").child("CurrentCompositionTextureSize").attribute("width").as_int();
    compResY = doc.child("XmlState").child("ScreenSetup").child("CurrentCompositionTextureSize").attribute("height").as_int();
    
    
    
    if (result2)    // if the xml is loaded in
    {
        for (pugi::xml_node screen: doc.child("XmlState").child("ScreenSetup").child("screens").children("Screen")) // for every Screen
        {
            for (pugi::xml_node slice: screen.child("layers").children("Slice"))    // for every slice
            {
                for (pugi::xml_node value: slice.child("InputRect").children("v"))  // for every v child
                {
                    xArray[vIndex] =  (value.attribute("x").as_double() / compResX) * 2. - 1.;
                    yArray[vIndex] =  (value.attribute("y").as_double() / compResY) * 2. - 1.;
                    vIndex++;   // vector index increment
                }
                sIndex++;    // screen index increment
                
                for (pugi::xml_node value: slice.child("OutputRect").children("v"))  // for every v child
                {
                    xArrayOut[vIndexOut] =  (value.attribute("x").as_double() / compResX) * 2. - 1.;
                    yArrayOut[vIndexOut] =  (value.attribute("y").as_double() / compResY) * 2. - 1.;
                    vIndexOut++;
                }
            }
        }
    }
    
    
    
    
    
    
    
    
}




