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
    
    // reset all values
    vIndex = 0;
    vIndexOut = 0;
    sIndex = 0;
    sliceIndex = 0;
    screenIndex = 0;
    for (int i=0;i<100;i++)
    {
        screenIndexArray[i] = 0;
    }
    for (int i=0;i<100;i++)
    {
        screenWidthArray[i] = 0;
    }
    for (int i=0;i<100;i++)
    {
        screenHeightArray[i] = 0;
    }
    
    pugi::xml_document doc;
    pugi::xml_parse_result
    result2 = doc.load_file(assFile.c_str());
    
    cout << "pugi is loaded? " << result2 << endl;
    cout << "Load result: " << result2.description() << endl;
    
    cout << endl;
    cout << "/////////////////////////////////////INFO/////////////////////////////////////" <<endl;
    cout << endl;
    
    compResX = doc.child("XmlState").child("ScreenSetup").child("CurrentCompositionTextureSize").attribute("width").as_int();
    compResY = doc.child("XmlState").child("ScreenSetup").child("CurrentCompositionTextureSize").attribute("height").as_int();
    
    
    if (compResX > 0 || compResY > 0)
    {
        olderResVersionDetected = false;
        if (result2)    // if the xml is loaded in
        {
            for (pugi::xml_node screen: doc.child("XmlState").child("ScreenSetup").child("screens").children("Screen")) // for every Screen
            {
                for (pugi::xml_node screenParam: screen.child("Params").children("Param")) //check if screen is enabled
                {
                    const char * str1 = screenParam.attribute("name").as_string();
                    const char * str2 = "Enabled";
                    int strncmpResult = strncmp(str1, str2, sizeof(&str2));
                    if (strncmpResult == 0)
                    {
                        if (screenParam.attribute("value").as_int() == 1)
                        {
                            screenNameArray[screenIndex] = screen.attribute("name").as_string();
                            
                            // get width and height of every screen
                            if (screen.child("OutputDevice").child("OutputDeviceVirtual").attribute("width").as_float() > 0)
                            {
                                screenResX = screen.child("OutputDevice").child("OutputDeviceVirtual").attribute("width").as_float();
                            }
                            else
                            {
                                screenResX = screen.child("OutputDevice").child("OutputDeviceDisplay").attribute("width").as_float();
                            }
                            screenWidthArray[screenIndex] = screenResX;
                            if (screen.child("OutputDevice").child("OutputDeviceVirtual").attribute("height").as_float() > 0)
                            {
                                screenResY = screen.child("OutputDevice").child("OutputDeviceVirtual").attribute("height").as_float();
                            }
                            else
                            {
                                screenResY = screen.child("OutputDevice").child("OutputDeviceDisplay").attribute("height").as_float();
                            }
                            screenHeightArray[screenIndex] = screenResY;
                            
                            cout << screenNameArray[screenIndex] << ": " << endl;
                            cout << "screenWidth " << screenWidthArray[screenIndex] << endl;
                            cout << "screenHeight " << screenHeightArray[screenIndex] << endl;
                            cout << endl;
                            
                            sliceIndex = 0;
                            for (pugi::xml_node slice: screen.child("layers").children("Slice")) // for every slice
                            {
                                for (pugi::xml_node sliceParam: slice.child("Params").children("Param"))
                                {
                                    const char * str1 = sliceParam.attribute("name").as_string();
                                    const char * str2 = "Enabled";
                                    int strncmpResult = strncmp(str1, str2, sizeof(&str2));
                                    if (strncmpResult == 0)
                                    {
                                        sliceEnabledArray[sIndex] = sliceParam.attribute("value").as_int();
                                    }
                                }
                                sliceName = slice.child("Params").child("Param").attribute("value").as_string();
                                sliceNameArray[sIndex] = sliceName;
                                
                                for (pugi::xml_node value: slice.child("InputRect").children("v"))  // for every input vextor
                                {
                                    xArray[vIndex] =  (value.attribute("x").as_double() / compResX) * 2. - 1.;
                                    yArray[vIndex] =  (value.attribute("y").as_double() / compResY) * 2. - 1.;
                                    vIndex++;   // vector index increment
                                }
                                sIndex++;    // slice index increment
                                
                                for (pugi::xml_node value: slice.child("OutputRect").children("v"))  // for every output vector
                                {
                                    xArrayOut[vIndexOut] =  (value.attribute("x").as_double() / screenResX) * 2. - 1.;
                                    yArrayOut[vIndexOut] =  (value.attribute("y").as_double() / screenResY) * 2. - 1.;
                                    vIndexOut++;
                                }
                                sliceIndex++;
                                screenIndexArray[screenIndex] = sliceIndex;
                            }
                            screenIndex++;
                        }
                    }
                }
            }
        }
    }
    else
    {
        olderResVersionDetected = true;
        cout << "!!OLDER RES VERSION DETECTED!! CAN'T SHOW INPUT MAP" << endl;
    }
    
    
    
    cout << "//////////////////////////////////////////////////////////////////////////////" <<endl;
}




