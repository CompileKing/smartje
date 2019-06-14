/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "../../HybridApi/Utilities/Utilities.h"

int screenSizeX = 1920;
int screenSizeY = 1080;

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
        
        float makeColor = i * 0.05;
        cout << makeColor << endl;

        auto sliceColor1  =  Colour::fromHSV (makeColor,    // hue
                                              1.f,    // saturation
                                              1.f,    // brightness
                                              1.0f);   // alpha,   // red
        
        
        auto sliceColor2  =  Colour::fromHSV (makeColor,    // hue
                                              1.f,    // saturation
                                              0.7f,    // brightness
                                              1.0f);   // alpha,   // red
        
        
        
        Rectangle<float> slice (x,y,width,height);
        g.fillCheckerBoard (slice, 10, 10, sliceColor1, sliceColor2);
        

        
        
    
        
        
        
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
