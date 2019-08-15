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
    arenaLAF.setColour(TextButton::buttonColourId, arenaTopGrey);
    arenaLAF.setColour(TextButton::textColourOnId, Colours::white);
    
    arenaLAF.setColour(ComboBox::backgroundColourId, arenaTopGrey);
    arenaLAF.setColour(ComboBox::outlineColourId, arenaBottomGrey);
    
    
    
    
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
    fileComp->setLookAndFeel(&arenaLAF);
    
    
    setSize(screenSizeX, screenSizeY);
    
    addAndMakeVisible(button1);
    button1.setVisible(0);
    button1.setButtonText("Input Map");
    button1.setBounds (260, 10, 130, 40);
    button1.addListener(this);
    button1.setLookAndFeel(&arenaLAF);
    
    
    
    addAndMakeVisible(button2);
    button2.setVisible(0);
    button2.setButtonText("Output Map");
    button2.setBounds (400, 10, 130, 40);
    button2.addListener(this);
    button2.setLookAndFeel(&arenaLAF);
    
    addAndMakeVisible(dec);
    dec.setVisible(0);
    dec.setButtonText("<");
    dec.setBounds (10, 60, 60, 40);
    dec.addListener(this);
    dec.setLookAndFeel(&arenaLAF);
    
    addAndMakeVisible(inc);
    inc.setVisible(0);
    inc.setButtonText(">");
    inc.setBounds(80, 60, 60, 40);
    inc.addListener(this);
    inc.setLookAndFeel(&arenaLAF);

}


MainComponent::~MainComponent()
{
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{
    
    zoomInOut = (sourceDistance / getWidth()) * 5.f;
    
    if (zoomInOut > lastZoomFrame)
    {
        
    }

    if (zoomInOut < lastZoomFrame)
    {
        
    }
    lastZoomFrame = zoomInOut;


    // draw Background Colour
    g.fillAll (arenaBottomGrey);
    
   
    
    // for every selected slice
    if (rect.olderResVersionDetected == false)
    {
        for (int i=sliceOffset;i<sliceMax;i++)
        {
            // get the right aspect ratio for the input map
            float compWidth = rect.compResX;
            float compHeight = rect.compResY;
            
            drawTheRightHeight = getWidth() * (compHeight / compWidth);
            
            // get the right aspect ratio for the output map (if there is one)
            if (currentScreen > 0)
            {
                getOutputScreenResolution(currentScreen);
                drawTheNormalHeight =
                    getWidth() * (outputScreenResolutionArray[1]/outputScreenResolutionArray[0]);
            }
            else
                drawTheNormalHeight = getWidth() * 0.5625;
            
            
            
            // create a different colour for each slice
            float sliceColor =  (i*0.1)/(rect.sIndex*0.1) + 0.1 ;
            // change opacity of slice based on if a slice is enabled in the xml
            if (rect.sliceEnabledArray[i] == 1)
                sliceOpacity = 0.6f;
            else
                sliceOpacity = 0.1f;
            auto tileColor1  =  Colour::fromHSV (sliceColor,1.f,1.f,sliceOpacity);
            if (drawInputMap)
            {
                drawV1x = (((rect.xArrayPtr[(4*i)]+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
                drawV1y = (((rect.yArrayPtr[(4*i)]+moveY)*zoomInOut)*0.5f+0.5f)*drawTheRightHeight;
                
                drawV2x = (((rect.xArrayPtr[(4*i)+1]+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
                drawV2y = (((rect.yArrayPtr[(4*i)+1]+moveY)*zoomInOut)*0.5f+0.5f)*drawTheRightHeight;
                
                drawV3x = (((rect.xArrayPtr[(4*i)+2]+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
                drawV3y = (((rect.yArrayPtr[(4*i)+2]+moveY)*zoomInOut)*0.5f+0.5f)*drawTheRightHeight;
                
                drawV4x = (((rect.xArrayPtr[(4*i)+3]+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
                drawV4y = (((rect.yArrayPtr[(4*i)+3]+moveY)*zoomInOut)*0.5f+0.5f)*drawTheRightHeight;
                // cout << "the right height: " << drawTheRightHeight << endl;
            }
            else
            {
                drawV1x = (((rect.xArrayOutPtr[(4*i)]+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
                drawV1y = (((rect.yArrayOutPtr[(4*i)]+moveY)*zoomInOut)*0.5f+0.5f)*drawTheNormalHeight;
                
                drawV2x = (((rect.xArrayOutPtr[(4*i)+1]+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
                drawV2y = (((rect.yArrayOutPtr[(4*i)+1]+moveY)*zoomInOut)*0.5f+0.5f)*drawTheNormalHeight;
                
                drawV3x = (((rect.xArrayOutPtr[(4*i)+2]+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
                drawV3y = (((rect.yArrayOutPtr[(4*i)+2]+moveY)*zoomInOut)*0.5f+0.5f)*drawTheNormalHeight;
                
                drawV4x = (((rect.xArrayOutPtr[(4*i)+3]+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
                drawV4y = (((rect.yArrayOutPtr[(4*i)+3]+moveY)*zoomInOut)*0.5f+0.5f)*drawTheNormalHeight;
                // cout << "the normal height: " << drawTheNormalHeight << endl;
            }
            
            // paint every slice as a path with a diffirent hue
            Path path;
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
            
            // paint an black outline and a cross over the slices
            Path stroke;
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

            // paint a black textbox in the center
            g.setColour(Colour::fromHSV(1, 0, 0.2, sliceOpacity));
            Rectangle<float> backSlice (path.getBounds().getCentreX()-(path.getBounds().getWidth()/4),
                                        path.getBounds().getCentreY()-(path.getBounds().getHeight()/4),
                                        path.getBounds().getWidth()/2,
                                        path.getBounds().getHeight()/2);
            g.fillRect(backSlice);
            
            Rectangle<float> textSlice (path.getBounds().getCentreX()-(path.getBounds().getWidth()/5),
                                        path.getBounds().getCentreY()-(path.getBounds().getHeight()/5),
                                        path.getBounds().getWidth()/2.5,
                                        path.getBounds().getHeight()/2.5);
            
            // paint the text overlay
            g.setFont (15.0f);
            g.setColour(Colour::fromFloatRGBA(1., 1., 1., sliceOpacity*1.666666));
            String name = rect.sliceNameArray[i];
            g.drawText(name, textSlice, Justification::centredTop);
            String size = "420 x 48";
            g.drawText(size, textSlice, Justification::centred);
            String info = "extra info";
            g.drawText(info, textSlice, Justification::centredBottom);
            
            // end of sliceloop
        }

        // draw input / output border edges
        if (drawInputMap == true)
        {
            float inputVector1x = (((-1.f+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
            float inputVector1y = (((-1.f+moveY)*zoomInOut)*0.5f+0.5f)*drawTheRightHeight;
            
            float inputVector2x = (((1.f+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
            float inputVector2y = (((-1.f+moveY)*zoomInOut)*0.5f+0.5f)*drawTheRightHeight;
            
            float inputVector3x = (((1.f+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
            float inputVector3y = (((1.f+moveY)*zoomInOut)*0.5f+0.5f)*drawTheRightHeight;
            
            float inputVector4x = (((-1.f+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
            float inputVector4y = (((1.f+moveY)*zoomInOut)*0.5f+0.5f)*drawTheRightHeight;
            
            Path compEdge;
            compEdge.startNewSubPath (Point<float>
                                      ( inputVector1x ,
                                       inputVector1y ));
            compEdge.lineTo (Point<float>
                             ( inputVector2x ,
                              inputVector2y ));
            compEdge.lineTo (Point<float>
                             ( inputVector3x ,
                              inputVector3y ));
            compEdge.lineTo (Point<float>
                             ( inputVector4x ,
                              inputVector4y ));
            compEdge.closeSubPath();
            
            
            g.setColour(arenaLessGreen);
            PathStrokeType pathStrokeType(1.f);
            float dashedLength[2];
            dashedLength[0]=4;
            dashedLength[1]=4;
            pathStrokeType.createDashedStroke(compEdge, compEdge, dashedLength, 2);
            g.strokePath(compEdge, pathStrokeType);
            
        }
        if (drawInputMap == false)
        {
            float inputVector1x = (((-1.f+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
            float inputVector1y = (((-1.f+moveY)*zoomInOut)*0.5f+0.5f)*drawTheNormalHeight;
            
            float inputVector2x = (((1.f+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
            float inputVector2y = (((-1.f+moveY)*zoomInOut)*0.5f+0.5f)*drawTheNormalHeight;
            
            float inputVector3x = (((1.f+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
            float inputVector3y = (((1.f+moveY)*zoomInOut)*0.5f+0.5f)*drawTheNormalHeight;
            
            float inputVector4x = (((-1.f+moveX)*zoomInOut)*0.5f+0.5f)*getWidth();
            float inputVector4y = (((1.f+moveY)*zoomInOut)*0.5f+0.5f)*drawTheNormalHeight
            ;
            Path compEdge;
            compEdge.startNewSubPath (Point<float>
                                      ( inputVector1x ,
                                       inputVector1y ));
            compEdge.lineTo (Point<float>
                             ( inputVector2x ,
                              inputVector2y ));
            compEdge.lineTo (Point<float>
                             ( inputVector3x ,
                              inputVector3y ));
            compEdge.lineTo (Point<float>
                             ( inputVector4x ,
                              inputVector4y ));
            compEdge.closeSubPath();

            g.setColour(arenaLessGreen);
            PathStrokeType pathStrokeType(1.f);
            float dashedLength[2];
            dashedLength[0]=4;
            dashedLength[1]=4;
            pathStrokeType.createDashedStroke(compEdge, compEdge, dashedLength, 2);
            g.strokePath(compEdge, pathStrokeType);
        }
        
        // incdec index label
        g.setColour(arenaTopGrey);
        g.fillRoundedRectangle(150, 60, 40, 40, 4);
        g.setColour(Colours::white);
        String incDecLabel;
        if (currentScreen > 0)
            incDecLabel = to_string(currentScreen);
        else if (currentScreen == 0)
            incDecLabel = "All";
        g.drawText(incDecLabel, 150, 60, 40, 40, Justification::centred);
        
    }
    // if an older version of resolume is detected don't draw anything but display this splashscreen
    else
    {
        g.setColour(Colours::orange);
        g.fillRect(0, 0, getWidth(), getHeight());
        String drawWarningText =
        "THIS SCREEN SETUP WAS MADE WITH AN OLDER VERSION OF RESOLUME AND THEREFORE CAN'T DISPLAY THE SLICES CORRECTLY, PLEASE USE THE LATEST VERSION";
        g.setColour(Colours::darkgrey);
        g.setFont(20.f);
        g.setFont (Font("Avenir Next", 30.f, Font::bold));
        g.drawMultiLineText(drawWarningText, getWidth()/4, getHeight()/4, getHeight());
    }
}


void MainComponent::resized()
{
    
}


