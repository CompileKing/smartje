/*
  ==============================================================================

    CreateSettingsFolder.cpp
    Created: 1 Oct 2019 2:47:45pm
    Author:  Sem Shimla

  ==============================================================================
*/

#include "CreateSettingsFolder.h"


CreateStarterXml::CreateStarterXml()
{
    //defaults
//    settingsFolderData = new XmlElement("SETTINGS");
    starterXml = juce::parseXML  (BinaryData::_smartjeKruisjes_xml);
    
}

CreateStarterXml::~CreateStarterXml()
{
//    settingsFolderData = nullptr;
}

bool CreateStarterXml::save()
{
    //save everything into an XML file
    File f = getXmlFile();
    if (! f.exists() )
    {
        firstTime = true;
        f.create();
        if (starterXml->writeTo(f))
            return true;
        else
        {
            DBG("SAVE ERROR!");
            return false;
        }
    }
    else
        firstTime = false;
}

File CreateStarterXml::getXmlFile()
{
    //get the file config.xml from the users documents folder
    File appDir = File::getSpecialLocation(File::userDocumentsDirectory);
    File xmlFile = appDir.getChildFile("SmartjeStarter.xml");
    return xmlFile;
}
