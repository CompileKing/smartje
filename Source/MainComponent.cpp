/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "../../HybridApi/Utilities/Utilities.h"

int screenSizeX = 800;
int screenSizeY = 1000;

//==============================================================================
MainComponent::MainComponent()
{
    
    rect.getInputRect();
    setSize (screenSizeX, screenSizeY);
    
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    
    g.fillAll (Colours::darkgrey);
    g.setColour (Colours::darkblue);
    /*
    g.setFont (14.0f);
    g.drawText ("jemoeder" , getLocalBounds(), Justification::centred, true);
     */
    
    g.setColour (Colours::sandybrown);
    
    for (int i=0;i<rect.sIndex;i++)
    {
   
        float x =         rect.xArrayPtr[(4*i)]*screenSizeX;
        float y =         rect.yArrayPtr[(4*i)]*screenSizeY;
        float width =     (rect.xArrayPtr[(4*i+1)] - rect.xArrayPtr[(4*i)])*screenSizeX;
        float height =    (rect.yArrayPtr[(4*i+3)] - rect.yArrayPtr[(4*i+1)])*screenSizeY;
        
        Rectangle<float> slice (x,y,width,height);
        g.fillCheckerBoard (slice, 10, 10, Colours::sandybrown, Colours::saddlebrown);
        
        g.setColour (Colours::black);
        g.drawRect(x, y, width, height);
        
        
        //g.drawRect(x,y,width,height);
        
        
    }
    


    
    
    
    
    
    
    
    
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
