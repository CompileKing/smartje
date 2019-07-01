/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


int screenSizeX = 1136;
int screenSizeY = 640;

//1136 x 640 pixels

//==============================================================================
MainComponent::MainComponent()
{
    
    
    
    addMouseListener(this, true);
    
    fileComp.reset(new FilenameComponent("fileComp",
                                         {},                       // current file
                                         false,                    // can edit file name,
                                         false,                    // is directory,
                                         false,                    // is for saving,
                                         {},                       // browser wildcard suffix,
                                         {},                       // enforced suffix,
                                         "Select file to open"));  // text when nothing selected
    addAndMakeVisible(fileComp.get());
    fileComp->addListener(this);
    fileComp->setBounds(10, 10, 240, 40);
    
    setSize(screenSizeX, screenSizeY);
    dragUp = 1;
    
}



MainComponent::~MainComponent()
{
}


/*
void MainComponent::mouseDragOne (const MouseEvent& e)
{
    dragUp = ((e.position.x / getWidth()*10) + 1);
    repaint();
}
 */

 

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    
    dragUp = (sourceDistance / getWidth()) * 10.f;
    
    g.fillAll (Colour::fromHSV(0.f, 0.f, 0.4, 1.f));

    for (int i=0;i<rect.sIndex;i++)
    {
        float sliceColor =  (i*0.1)/(rect.sIndex*0.1) + 0.1 ;// create a different colour for each slice
        auto tileColor1  =  Colour::fromHSV (sliceColor,     // hue
                                              1.f,           // saturation
                                              1.f,           // brightness
                                              0.6f);         // alpha,
        
        Path path; // paint every slice as a path with a diffirent hue
        path.startNewSubPath (Point<float> ( ((rect.xArrayPtr[(4*i)]*dragUp)*0.5+0.5)*getWidth() ,
                                             ((rect.yArrayPtr[(4*i)]*dragUp)*0.5+0.5)*getHeight() ));
        
        path.lineTo (Point<float>          ( ((rect.xArrayPtr[(4*i+1)]*dragUp)*0.5+0.5)*getWidth() ,
                                             ((rect.yArrayPtr[(4*i+1)]*dragUp)*0.5+0.5)*getHeight() ));
        
        path.lineTo (Point<float>          ( ((rect.xArrayPtr[(4*i+2)]*dragUp)*0.5+0.5)*getWidth() ,
                                             ((rect.yArrayPtr[(4*i+2)]*dragUp)*0.5+0.5)*getHeight() ));
        
        path.lineTo (Point<float>          ( ((rect.xArrayPtr[(4*i+3)]*dragUp)*0.5+0.5)*getWidth() ,
                                             ((rect.yArrayPtr[(4*i+3)]*dragUp)*0.5+0.5)*getHeight() ));
        path.closeSubPath();
        g.setColour(tileColor1);
        g.fillPath (path);
        
        
        
        
        Path stroke; // paint an black outline and a cross over the slices
        stroke.startNewSubPath (Point<float> ( ((rect.xArrayPtr[(4*i)]*dragUp)*0.5+0.5)*getWidth() ,
                                               ((rect.yArrayPtr[(4*i)]*dragUp)*0.5+0.5)*getHeight() ));
        
        stroke.lineTo (Point<float>          ( ((rect.xArrayPtr[(4*i+2)]*dragUp)*0.5+0.5)*getWidth() ,
                                               ((rect.yArrayPtr[(4*i+2)]*dragUp)*0.5+0.5)*getHeight() ));
        
        stroke.lineTo (Point<float>          ( ((rect.xArrayPtr[(4*i+1)]*dragUp)*0.5+0.5)*getWidth() ,
                                               ((rect.yArrayPtr[(4*i+1)]*dragUp)*0.5+0.5)*getHeight() ));
        
        stroke.lineTo (Point<float>          ( ((rect.xArrayPtr[(4*i+3)]*dragUp)*0.5+0.5)*getWidth() ,
                                               ((rect.yArrayPtr[(4*i+3)]*dragUp)*0.5+0.5)*getHeight() ));
        stroke.closeSubPath();
        g.setColour(Colour::fromHSV(1., 1., 0., 1.));
        g.strokePath(stroke, PathStrokeType(1.));
        g.strokePath(path, PathStrokeType(1.));
    
        g.setColour(Colour::fromHSV(1, 0, 0.2, 1)); // paint a black textbox in the center
        Rectangle<float> slice (path.getBounds().getCentreX()-30,path.getBounds().getCentreY()-20,60,40);
        g.fillRect(slice);

        g.setFont (20.0f); // paint the text overlay
        g.setColour (Colours::white);
        String text = "slice";
        g.drawText(text, path.getBounds(), Justification::centred);
        

    }

}

void MainComponent::resized()
{
	 
}
