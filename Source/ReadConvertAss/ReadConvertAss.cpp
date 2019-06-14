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




void InputRect::getInputRect()
{
#ifdef _WIN64
    string homePath1;
    
    WCHAR path[MAX_PATH + 1];
    if (SHGetSpecialFolderPathW(HWND_DESKTOP, path, CSIDL_PROFILE, FALSE))
    {
        std::wstring ws(path);
        std::string HOME1(ws.begin(), ws.end());
        string s11 = HOME1;
        string s12 = "\\Documents\\Resolume Arena 6\\Preferences\\AdvancedOutput.xml";
        homePath1 = s11 + s12;
    }
    
#else
    string  HOME1 = getenv("HOME") ? getenv("HOME") : ".";
    string homePath1;
    string s11 = HOME1;
    string s12 = "/Documents/Resolume Arena 6/Preferences/AdvancedOutput.xml";
    homePath1 = s11 + s12;
#endif
    
    cout << homePath1 << endl;
    
    pugi::xml_document ass;
    pugi::xml_parse_result
    result1 = ass.load_file(homePath1.c_str());
    
    if (result1)
    {
        assPath = ass.child("ScreenSetup").attribute("presetFile").as_string();
        assPath = assPath + ".xml";
    }
    
    
    //=====================================================================================
    //                       retrieved ASS PATH as string assPath
    //=====================================================================================
    
    
#ifdef _WIN64
    string homePath2;
    
    WCHAR path2[MAX_PATH + 1];
    if (SHGetSpecialFolderPathW(HWND_DESKTOP, path2, CSIDL_PROFILE, FALSE))
    {
        std::wstring ws(path2);
        std::string HOME2(ws.begin(), ws.end());
        string s21 = HOME2;
        string s22 = "\\Documents\\Resolume Arena 6\\Presets\\Advanced Output\\";
        string s23 = assPath;
        homePath2 = s21 + s22 + s23;
    }
    
#else
    string  HOME2 = getenv("HOME") ? getenv("HOME") : ".";
    string homePath2;
    string s21 = HOME2;
    string s22 = "/Documents/Resolume Arena 6/Presets/Advanced Output/";
    string s23 = assPath;
    homePath2 = s21 + s22 + s23;
    
    cout << homePath2 << endl;
    cout << endl;
#endif
    
    
    pugi::xml_document doc;
    pugi::xml_parse_result
    result2 = doc.load_file(homePath2.c_str());
    
    compResX = doc.child("XmlState").child("ScreenSetup").child("CurrentCompositionTextureSize").attribute("width").as_int();
    compResY = doc.child("XmlState").child("ScreenSetup").child("CurrentCompositionTextureSize").attribute("height").as_int();
    
    if (result2)    // if the xml is loaded in
    {
        for (pugi::xml_node screen: doc.child("XmlState").child("ScreenSetup").child("screens").children("Screen")) // for every Screen
        {
            if (strncmp (screen.attribute("name").as_string(),"Tracer",6) == 0) // for every Screen called Tracer
            {
                for (pugi::xml_node slice: screen.child("layers").children("Slice"))    // for every slice
                    
                {
                    for (pugi::xml_node value: slice.child("InputRect").children("v"))  // for every v child
                    {
                        xArray[vIndex] =  (value.attribute("x").as_double() / compResX);  // get x attribute and fill xArray and normalise with comp width
                        yArray[vIndex] =  (value.attribute("y").as_double() / compResY);  // get y attribute and fill yArray and normalise with comp height
                        
                        vIndex++;   // vector index increment
                    }
                    sIndex++;    // screen index increment
                }
            }
        }
    }
    
    
    
}




