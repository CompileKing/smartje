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
    button1.setBounds (260, 10, 130, 40);
    button1.addListener(this);
    
    addAndMakeVisible(button2);
    button2.setButtonText("Output Map");
    button2.setBounds (410, 10, 130, 40);
    button2.addListener(this);
    
    addAndMakeVisible(screen1);
    addAndMakeVisible(screen2);
    addAndMakeVisible(screen3);
    addAndMakeVisible(screen4);
    addAndMakeVisible(screen5);
    addAndMakeVisible(screen6);
    addAndMakeVisible(screen7);
    addAndMakeVisible(screen8);
    
    screen1.setBounds (10, 60, 180, 22);
    screen2.setBounds (10, 60 + (22 * 1), 180, 22);
    screen3.setBounds (10, 60 + (22 * 2), 180, 22);
    screen4.setBounds (10, 60 + (22 * 3), 180, 22);
    screen5.setBounds (10, 60 + (22 * 4), 180, 22);
    screen6.setBounds (10, 60 + (22 * 5), 180, 22);
    screen7.setBounds (10, 60 + (22 * 6), 180, 22);
    screen8.setBounds (10, 60 + (22 * 7), 180, 22);
    
    screen1.setRadioGroupId (GenderButtons);
    screen2.setRadioGroupId (GenderButtons);
    screen3.setRadioGroupId (GenderButtons);
    screen4.setRadioGroupId (GenderButtons);
    screen5.setRadioGroupId (GenderButtons);
    screen6.setRadioGroupId (GenderButtons);
    screen7.setRadioGroupId (GenderButtons);
    screen8.setRadioGroupId (GenderButtons);
    
    screen1.onClick = [this] { updateToggleState (&screen1, 1); };
    screen2.onClick = [this] { updateToggleState (&screen2, 2); };
    screen3.onClick = [this] { updateToggleState (&screen3, 3); };
    screen4.onClick = [this] { updateToggleState (&screen4, 4); };
    screen5.onClick = [this] { updateToggleState (&screen5, 5); };
    screen6.onClick = [this] { updateToggleState (&screen6, 6); };
    screen7.onClick = [this] { updateToggleState (&screen7, 7); };
    screen8.onClick = [this] { updateToggleState (&screen8, 8); };
    
    screen1.setVisible(0);
    screen2.setVisible(0);
    screen3.setVisible(0);
    screen4.setVisible(0);
    screen5.setVisible(0);
    screen6.setVisible(0);
    screen7.setVisible(0);
    screen8.setVisible(0);
    
    

}


MainComponent::~MainComponent()
{
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{
    dragUp = (sourceDistance / getWidth()) * 10.f;
    g.fillAll (Colour::fromHSV(0.f, 0.f, 0., 0.1f));

    for (int i=sliceOffset;i<sliceMax;i++) // for every slice
    {
        /*
        cout << "name of slice: " << rect.sliceNameArray[i] << endl;
        cout << "is slice enabled: " << rect.sliceEnabledArray[i] << endl;
         */
        
        float compWidth = rect.compResX; // get the right aspect ratio for the input map
        float compHeight = rect.compResY;
        drawTheRightHeight = getWidth() * (compHeight / compWidth);
        
        drawTheNormalHeight = getWidth() * 0.5625; // get the normal 16:9 aspect ratio for the output map

        float sliceColor =  (i*0.1)/(rect.sIndex*0.1) + 0.1 ;// create a different colour for each slice
        if (rect.sliceEnabledArray[i] == 1) // change opacity of slice based on if a slice is enabled in the xml
            sliceOpacity = 0.6f;
        else
            sliceOpacity = 0.1f;
        auto tileColor1  =  Colour::fromHSV (sliceColor,     // hue
                                              1.f,           // saturation
                                              1.f,           // brightness
                                              sliceOpacity);         // alpha,
        if (drawInputMap)
        {
            drawV1x = (((rect.xArrayPtr[(4*i)]+moveX)*dragUp)*0.5f+0.5f)*getWidth();
            drawV1y = (((rect.yArrayPtr[(4*i)]+moveY)*dragUp)*0.5f+0.5f)*drawTheRightHeight;
            
            drawV2x = (((rect.xArrayPtr[(4*i)+1]+moveX)*dragUp)*0.5f+0.5f)*getWidth();
            drawV2y = (((rect.yArrayPtr[(4*i)+1]+moveY)*dragUp)*0.5f+0.5f)*drawTheRightHeight;
            
            drawV3x = (((rect.xArrayPtr[(4*i)+2]+moveX)*dragUp)*0.5f+0.5f)*getWidth();
            drawV3y = (((rect.yArrayPtr[(4*i)+2]+moveY)*dragUp)*0.5f+0.5f)*drawTheRightHeight;
            
            drawV4x = (((rect.xArrayPtr[(4*i)+3]+moveX)*dragUp)*0.5f+0.5f)*getWidth();
            drawV4y = (((rect.yArrayPtr[(4*i)+3]+moveY)*dragUp)*0.5f+0.5f)*drawTheRightHeight;
            // cout << "the right height: " << drawTheRightHeight << endl;
        }
        else
        {
            drawV1x = (((rect.xArrayOutPtr[(4*i)]+moveX)*dragUp)*0.5f+0.5f)*getWidth();
            drawV1y = (((rect.yArrayOutPtr[(4*i)]+moveY)*dragUp)*0.5f+0.5f)*drawTheNormalHeight;
            
            drawV2x = (((rect.xArrayOutPtr[(4*i)+1]+moveX)*dragUp)*0.5f+0.5f)*getWidth();
            drawV2y = (((rect.yArrayOutPtr[(4*i)+1]+moveY)*dragUp)*0.5f+0.5f)*drawTheNormalHeight;
            
            drawV3x = (((rect.xArrayOutPtr[(4*i)+2]+moveX)*dragUp)*0.5f+0.5f)*getWidth();
            drawV3y = (((rect.yArrayOutPtr[(4*i)+2]+moveY)*dragUp)*0.5f+0.5f)*drawTheNormalHeight;
            
            drawV4x = (((rect.xArrayOutPtr[(4*i)+3]+moveX)*dragUp)*0.5f+0.5f)*getWidth();
            drawV4y = (((rect.yArrayOutPtr[(4*i)+3]+moveY)*dragUp)*0.5f+0.5f)*drawTheNormalHeight;
            // cout << "the normal height: " << drawTheNormalHeight << endl;
        }
        

        Path path; // paint every slice as a path with a diffirent hue
        path.startNewSubPath (Point<float>
                     ( drawV1x ,
                       drawV1y ));
        path.lineTo (Point<float>
                     ( drawV2x ,
                       drawV2y ));
        path.lineTo (Point<float>
                     ( drawV3x ,
                       drawV3y ));
        path.lineTo (Point<float>
                     ( drawV4x ,
                       drawV4y ));
        path.closeSubPath();
        g.setColour(tileColor1);
        g.fillPath (path);

        
        Path stroke; // paint an black outline and a cross over the slices
        stroke.startNewSubPath (Point<float>
                     ( drawV1x ,
                       drawV1y ));
        stroke.lineTo (Point<float>
                     ( drawV3x ,
                       drawV3y ));
        stroke.lineTo (Point<float>
                     ( drawV2x ,
                       drawV2y ));
        stroke.lineTo (Point<float>
                     ( drawV4x ,
                       drawV4y ));
        stroke.closeSubPath();
        g.setColour(Colour::fromHSV(1., 1., 0., sliceOpacity));
        g.strokePath(stroke, PathStrokeType(1.));
        g.strokePath(path, PathStrokeType(1.));
        
        

        g.setColour(Colour::fromHSV(1, 0, 0.2, sliceOpacity)); // paint a black textbox in the center
        Rectangle<float> backSlice (path.getBounds().getCentreX()-(path.getBounds().getWidth()/4),
                                path.getBounds().getCentreY()-(path.getBounds().getHeight()/4),
                                path.getBounds().getWidth()/2,
                                path.getBounds().getHeight()/2);
        g.fillRect(backSlice);
        
        Rectangle<float> textSlice (path.getBounds().getCentreX()-(path.getBounds().getWidth()/5),
                                    path.getBounds().getCentreY()-(path.getBounds().getHeight()/5),
                                    path.getBounds().getWidth()/2.5,
                                    path.getBounds().getHeight()/2.5);

        g.setFont (15.0f); // paint the text overlay
        g.setColour(Colour::fromFloatRGBA(1., 1., 1., sliceOpacity*1.666666));
        String name = rect.sliceNameArray[i];
        g.drawText(name, textSlice, Justification::centredTop);
        String size = "420 x 48";
        g.drawText(size, textSlice, Justification::centred);
        String info = "extra info";
        g.drawText(info, textSlice, Justification::centredBottom);
   
    }

}

void MainComponent::resized()
{
	 
}


