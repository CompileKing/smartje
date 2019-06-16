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
    
    g.fillAll (Colours::darkgrey);

    for (int i=0;i<rect.sIndex;i++)
    {
   
        float x =         rect.xArrayPtr[(4*i)] * screenSizeX;
        float y =         rect.yArrayPtr[(4*i)] * screenSizeY;
        float width =     (rect.xArrayPtr[(4*i+1)] - rect.xArrayPtr[(4*i)]) * screenSizeX;
        float height =    (rect.yArrayPtr[(4*i+3)] - rect.yArrayPtr[(4*i+1)]) * screenSizeY;
        
        float sliceColor = (i*0.1)/(rect.sIndex*0.1) ;
        
        
        /*
        rect.xArrayPtr[(4*i)],  rect.yArrayPtr[(4*i)],      //top left
        rect.xArrayPtr[(4*i+1)],rect.yArrayPtr[(4*i+1)],    //top right
        rect.xArrayPtr[(4*i+2)],rect.yArrayPtr[(4*i+2)],    //bottom right
        rect.xArrayPtr[(4*i+3)],rect.yArrayPtr[(4*i+3)],
         
         */
        

        auto tileColor1  =  Colour::fromHSV (sliceColor,    // hue
                                              1.f,    // saturation
                                              1.f,    // brightness
                                              0.6f);   // alpha,   // red
        
        
        auto tileColor2  =  Colour::fromHSV (sliceColor,    // hue
                                              1.f,    // saturation
                                              0.7f,    // brightness
                                              0.6f);   // alpha,   // red
        
        
        
        Rectangle<float> slice (x,y,width,height);
        
        
        
        
         Path path;
         path.startNewSubPath (Point<float> (rect.xArrayPtr[(4*i)] * screenSizeX , rect.yArrayPtr[(4*i)] * screenSizeY));
         path.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+1] * screenSizeX , rect.yArrayPtr[(4*i)+1] * screenSizeY));
         path.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+2] * screenSizeX , rect.yArrayPtr[(4*i)+2] * screenSizeY));
         path.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+3] * screenSizeX , rect.yArrayPtr[(4*i)+3] * screenSizeY));
         path.closeSubPath();
        g.setColour(tileColor1);
         g.fillPath (path);
        
         
        
        
        
        
        
        
        
        g.setFont (20.0f);
        g.setColour (Colours::white);
        g.drawText("smartAss", x, y, width, height,Justification::centred);
        g.setColour (Colours::black);
        
        
        
        
    
    }

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
