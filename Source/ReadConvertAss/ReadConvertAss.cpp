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


void InputRect::getInputRect(std::string assFile)
{
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
            screenNameArray[screenIndex] = screen.attribute("name").as_string();
            for (pugi::xml_node screenParam: screen.child("Params").children("Param"))
            {
                const char * str1 = screenParam.attribute("name").as_string();
                const char * str2 = "Enabled";
                int strncmpResult = strncmp(str1, str2, sizeof(&str2));
                if (strncmpResult == 0)
                {
                    if (screenParam.attribute("value").as_int() == 1)
                    {
                        screenIndex++; // slice index increment
                        for (pugi::xml_node slice: screen.child("layers").children("Slice")) // for every slice
                        {
                            
                            for (pugi::xml_node value: slice.child("InputRect").children("v"))  // for every input vextor
                            {
                                xArray[vIndex] =  (value.attribute("x").as_double() / compResX) * 2. - 1.;
                                yArray[vIndex] =  (value.attribute("y").as_double() / compResY) * 2. - 1.;
                                vIndex++;   // vector index increment
                            }
                            sIndex++;    // slice index increment
                            
                            for (pugi::xml_node value: slice.child("OutputRect").children("v"))  // for every output vector
                            {
                                xArrayOut[vIndexOut] =  (value.attribute("x").as_double() / compResX) * 2. - 1.;
                                yArrayOut[vIndexOut] =  (value.attribute("y").as_double() / compResY) * 2. - 1.;
                                vIndexOut++;
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    
    
    
    
    
    
}




