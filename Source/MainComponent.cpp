/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "../../HybridApi/Utilities/Utilities.h"

int screenSizeX = 1920/2;
int screenSizeY = 1080/2;

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

    
    g.setColour (Colours::sandybrown);
    
    for (int i=0;i<rect.sIndex;i++)
    {
   
        float x =         rect.xArrayPtr[(4*i)]*screenSizeX;
        float y =         rect.yArrayPtr[(4*i)]*screenSizeY;
        float width =     (rect.xArrayPtr[(4*i+1)] - rect.xArrayPtr[(4*i)])*screenSizeX;
        float height =    (rect.yArrayPtr[(4*i+3)] - rect.yArrayPtr[(4*i+1)])*screenSizeY;
        
        float sliceColor = (i*0.1)/(rect.sIndex*0.1);
        cout << sliceColor << endl;

        auto tileColor1  =  Colour::fromHSV (sliceColor,    // hue
                                              1.f,    // saturation
                                              1.f,    // brightness
                                              0.6f);   // alpha,   // red
        
        
        auto tileColor2  =  Colour::fromHSV (sliceColor,    // hue
                                              1.f,    // saturation
                                              0.7f,    // brightness
                                              0.6f);   // alpha,   // red
        
        Rectangle<float> slice (x,y,width,height);
        g.fillCheckerBoard (slice, 10, 10, tileColor1, tileColor2);
        
        g.setFont (20.0f);
        g.setColour (Colours::white);
        g.drawText("smartAss", x, y, width, height,Justification::centred);
        g.setColour (Colours::black);
        g.drawRect(x, y, width, height);
        
        
        
    
    }

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
