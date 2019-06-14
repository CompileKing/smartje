/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "../../HybridApi/Utilities/Utilities.h"

int screenSizeX = 600;
int screenSizeY = 400;

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
        /*
            rect.xArrayPtr[(4*i)],  rect.yArrayPtr[(4*i)],      //top left
            rect.xArrayPtr[(4*i+1)],rect.yArrayPtr[(4*i+1)],    //top right
            rect.xArrayPtr[(4*i+2)],rect.yArrayPtr[(4*i+2)],    //bottom right
            rect.xArrayPtr[(4*i+3)],rect.yArrayPtr[(4*i+3)],    //bottom left
         */
        
        int x =         rect.xArrayPtr[(4*i)]*screenSizeX;
        int y =         rect.yArrayPtr[(4*i)]*screenSizeY;
        int width =     (rect.xArrayPtr[(4*i+1)] - rect.xArrayPtr[(4*i)])*screenSizeY;
        int height =    (rect.yArrayPtr[(4*i+2)] - rect.yArrayPtr[(4*i+1)])*screenSizeY;
        
        g.drawRect(x,y,width,height);
        
        
    }
    


    
    
    
    
    
    
    
    
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
