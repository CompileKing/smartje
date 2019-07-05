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
    
    addAndMakeVisible(button1);
    button1.setButtonText("Input Map");
    button1.setBounds (260, 10, 160, 40);
    button1.addListener(this);
    
    addAndMakeVisible(button2);
    button2.setButtonText("Output Map");
    button2.setBounds (430, 10, 160, 40);
    button2.addListener(this);
}



MainComponent::~MainComponent()
{
}


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
        if (drawInputMap)
        {
            drawV1x = rect.xArrayPtr[(4*i)];
            drawV1y = rect.yArrayPtr[(4*i)];
            
            drawV2x = rect.xArrayPtr[(4*i+1)];
            drawV2y = rect.yArrayPtr[(4*i+1)];
            
            drawV3x = rect.xArrayPtr[(4*i+2)];
            drawV3y = rect.yArrayPtr[(4*i+2)];
            
            drawV4x = rect.xArrayPtr[(4*i+3)];
            drawV4y = rect.yArrayPtr[(4*i+3)];
        }
        else
        {
            drawV1x = rect.xArrayOutPtr[(4*i)];
            drawV1y = rect.yArrayOutPtr[(4*i)];
            
            drawV2x = rect.xArrayOutPtr[(4*i+1)];
            drawV2y = rect.yArrayOutPtr[(4*i+1)];
            
            drawV3x = rect.xArrayOutPtr[(4*i+2)];
            drawV3y = rect.yArrayOutPtr[(4*i+2)];
            
            drawV4x = rect.xArrayOutPtr[(4*i+3)];
            drawV4y = rect.yArrayOutPtr[(4*i+3)];
        }
        cout << "drawInputMap?: " << drawInputMap << endl;
       
        
        Path path; // paint every slice as a path with a diffirent hue
        path.startNewSubPath (Point<float>
                     ( (((drawV1x+moveX)*dragUp)*0.5+0.5)*getWidth() ,
                       (((drawV1y+moveY)*dragUp)*0.5+0.5)*getHeight() ));
        
        path.lineTo (Point<float>
                     ( (((drawV2x+moveX)*dragUp)*0.5+0.5)*getWidth() ,
                       (((drawV2y+moveY)*dragUp)*0.5+0.5)*getHeight() ));
        
        path.lineTo (Point<float>
                     ( (((drawV3x+moveX)*dragUp)*0.5+0.5)*getWidth() ,
                       (((drawV3y+moveY)*dragUp)*0.5+0.5)*getHeight() ));
        
        path.lineTo (Point<float>
                     ( (((drawV4x+moveX)*dragUp)*0.5+0.5)*getWidth() ,
                       (((drawV4y+moveY)*dragUp)*0.5+0.5)*getHeight() ));
        path.closeSubPath();
        g.setColour(tileColor1);
        g.fillPath (path);

        
        Path stroke; // paint an black outline and a cross over the slices
        stroke.startNewSubPath (Point<float>
                     ( (((drawV1x+moveX)*dragUp)*0.5+0.5)*getWidth() ,
                       (((drawV1y+moveY)*dragUp)*0.5+0.5)*getHeight() ));
        
        stroke.lineTo (Point<float>
                     ( (((drawV3x+moveX)*dragUp)*0.5+0.5)*getWidth() ,
                       (((drawV3y+moveY)*dragUp)*0.5+0.5)*getHeight() ));
        
        stroke.lineTo (Point<float>
                     ( (((drawV2x+moveX)*dragUp)*0.5+0.5)*getWidth() ,
                       (((drawV2y+moveY)*dragUp)*0.5+0.5)*getHeight() ));
        
        stroke.lineTo (Point<float>
                     ( (((drawV4x+moveX)*dragUp)*0.5+0.5)*getWidth() ,
                       (((drawV4y+moveY)*dragUp)*0.5+0.5)*getHeight() ));
        stroke.closeSubPath();
        g.setColour(Colour::fromHSV(1., 1., 0., 1.));
        g.strokePath(stroke, PathStrokeType(1.));
        g.strokePath(path, PathStrokeType(1.));

        g.setColour(Colour::fromHSV(1, 0, 0.2, 0.8)); // paint a black textbox in the center
        Rectangle<float> slice (path.getBounds().getCentreX()-(path.getBounds().getWidth()/5),
                                path.getBounds().getCentreY()-(path.getBounds().getHeight()/5),
                                path.getBounds().getWidth()/2.5,
                                path.getBounds().getHeight()/2.5);
        g.fillRect(slice);

        g.setFont (15.0f); // paint the text overlay
        g.setColour (Colours::white);
        String name = "slice name";
        g.drawText(name, slice, Justification::centredTop);
        String size = "420 x 48";
        g.drawText(size, slice, Justification::centred);
        String info = "extra info";
        g.drawText(info, slice, Justification::centredBottom);
        
        
        
        
    }

}

void MainComponent::resized()
{
	 
}


