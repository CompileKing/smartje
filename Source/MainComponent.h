/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReadConvertAss/ReadConvertAss.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
						public FilenameComponentListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged) override
	{
		if (fileComponentThatHasChanged == fileComp.get())
			readFile(fileComp->getCurrentFile());
	}

	void readFile(const File& fileToRead)
	{
		if (!fileToRead.existsAsFile()) // [1]
			return;

		auto fileText = fileToRead.loadFileAsString();
		auto filePath = fileToRead.getFullPathName();
		std::cout << filePath << std::endl;
	}


	

private:
    //==============================================================================
    // Your private member variables go here...
    
    InputRect rect;
    
    void mouseDrag (const MouseEvent& e) override;
    float clickColour;
	std::unique_ptr<FilenameComponent> fileComp;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
