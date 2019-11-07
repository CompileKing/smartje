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
    setSize(screenSizeX, screenSizeY);
    
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
                                         "Open File"));  // text when nothing selected
    addAndMakeVisible(fileComp.get());
    fileComp->addListener(this);
    fileComp->setBounds (0, 0, 180+1, 40);
    fileComp->setLookAndFeel(&arenaLAF);
        
    addAndMakeVisible(button1);
    button1.setVisible(1);
    button1.setButtonText("Input");
    button1.setBounds   (0, 40+1, 90, 40);
    button1.addListener(this);
    button1.setLookAndFeel(&arenaLAF);

    addAndMakeVisible(button2);
    button2.setVisible(1);
    button2.setButtonText("Output");
    button2.setBounds   (90+1, 40+1, 90, 40);
    button2.addListener(this);
    button2.setLookAndFeel(&arenaLAF);
    
    addAndMakeVisible(dec);
    dec.setVisible(1);
    dec.setButtonText("<");
    dec.setBounds       (0, 80+2, 60, 40);
    dec.addListener(this);
    dec.setLookAndFeel(&arenaLAF);
    
    addAndMakeVisible(inc);
    inc.setVisible(1);
    inc.setButtonText(">");
    inc.setBounds       (60+1, 80+2, 60, 40);
    inc.addListener(this);
    inc.setLookAndFeel(&arenaLAF);

    addAndMakeVisible(mouseInputLabel1);
    addAndMakeVisible(mouseInputLabel2);
    addAndMakeVisible(sourceDistanceLabel);
}


MainComponent::~MainComponent()
{
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{    
    // draw Background Colour
    g.fillAll (arenaBottomGrey);
    
    // draw input / output border edges
    Path compEdge;
    float inputVector1x;
    float inputVector1y;
    float inputVector2x;
    float inputVector2y;
    float inputVector3x;
    float inputVector3y;
    float inputVector4x;
    float inputVector4y;
    
    if (drawInputMap == true)
    {
        inputVector1x = moveZoom(-1.f,1) * getWidth();
        inputVector1y = moveZoom(-1.f,0) * drawInputHeight;
        inputVector2x = moveZoom(1.f,1) * getWidth();
        inputVector2y = moveZoom(-1.f,0) * drawInputHeight;
        inputVector3x = moveZoom(1.f,1) * getWidth();
        inputVector3y = moveZoom(1.f,0) * drawInputHeight;
        inputVector4x = moveZoom(-1.f,1) * getWidth();
        inputVector4y = moveZoom(1.f,0) * drawInputHeight;
    }
    if (drawInputMap == false)
    {
        inputVector1x = moveZoom(-1.f,1) * getWidth();
        inputVector1y = moveZoom(-1.f,0) * drawOutputHeight;
        inputVector2x = moveZoom(1.f,1) * getWidth();
        inputVector2y = moveZoom(-1.f,0) * drawOutputHeight;
        inputVector3x = moveZoom(1.f,1) * getWidth();
        inputVector3y = moveZoom(1.f,0) * drawOutputHeight;
        inputVector4x = moveZoom(-1.f,1) * getWidth();
        inputVector4y = moveZoom(1.f,0) * drawOutputHeight;
    }
    
    compEdge.startNewSubPath (Point<float>( inputVector1x ,inputVector1y ));
    compEdge.lineTo (Point<float>(inputVector2x, inputVector2y));
    compEdge.lineTo (Point<float>(inputVector3x, inputVector3y));
    compEdge.lineTo (Point<float>(inputVector4x, inputVector4y));
    compEdge.closeSubPath();
    
    // draw a workField
    g.setColour(Colours::white.withAlpha(0.05f));
    g.fillPath(compEdge);
        
    // for every selected slice
    if (rect.olderResVersionDetected == false)
    {
        for (int i=sliceOffset;i<sliceMax;i++)
        {
            // create raw slices to calculate width and height for input and output......
            float rawVector1x;
            float rawVector1y;
            float rawVector2x;
            float rawVector2y;
            float rawVector3x;
            float rawVector3y;
            float rawVector4x;
            float rawVector4y;
            if (drawInputMap)
            {
                rawVector1x = rect.xArrayRaw[(4*i)];
                rawVector1y = rect.yArrayRaw[(4*i)];
                rawVector2x = rect.xArrayRaw[(4*i)+1];
                rawVector2y = rect.yArrayRaw[(4*i)+1];
                rawVector3x = rect.xArrayRaw[(4*i)+2];
                rawVector3y = rect.yArrayRaw[(4*i)+2];
                rawVector4x = rect.xArrayRaw[(4*i)+3];
                rawVector4y = rect.yArrayRaw[(4*i)+3];
            }
            else
            {
                rawVector1x = rect.xArrayOutRaw[(4*i)];
                rawVector1y = rect.yArrayOutRaw[(4*i)];
                rawVector2x = rect.xArrayOutRaw[(4*i)+1];
                rawVector2y = rect.yArrayOutRaw[(4*i)+1];
                rawVector3x = rect.xArrayOutRaw[(4*i)+2];
                rawVector3y = rect.yArrayOutRaw[(4*i)+2];
                rawVector4x = rect.xArrayOutRaw[(4*i)+3];
                rawVector4y = rect.yArrayOutRaw[(4*i)+3];
            }
            
            // create invisible 'raw' slices
            Path raw;
            raw.startNewSubPath (Point<float>(rawVector1x ,rawVector1y));
            raw.lineTo (Point<float>(rawVector2x ,rawVector2y));
            raw.lineTo (Point<float>(rawVector3x ,rawVector3y));
            raw.lineTo (Point<float>(rawVector4x ,rawVector4y));
            raw.closeSubPath();
            
            {
                // do a kickflip
                Point<float> center = raw.getBounds().getCentre();
                if (drawInputMap)
                {
                    raw.applyTransform( AffineTransform::rotation( -rect.inputSliceRotationArray[i], center.x, center.y ));
                    SliceWidth = raw.getBounds().getWidth();
                    SliceHeight = raw.getBounds().getHeight();
                }
                
                else
                {
                    raw.applyTransform(AffineTransform::rotation(-rect.outputSliceRotationArray[i], center.x, center.y ));
                    SliceWidth = raw.getBounds().getWidth();
                    SliceHeight = raw.getBounds().getHeight();
                }
            }
            
            // create a different colour for each slice
//            float sliceColor =  (i*0.1)/(rect.sIndex*0.1) + 0.1 ;
            // change opacity of slice based on if a slice is enabled in the xml
            if (rect.sliceEnabledArray[i] == 1)
                sliceOpacity = 0.9f;
            else
                sliceOpacity = 0.1f;
//            auto tileColor1  =  Colour::fromHSV (sliceColor,1.f,1.f,sliceOpacity);
            if (drawInputMap)
            {
                drawV1x = moveZoom(rect.xArrayPtr[(4*i)],1) * getWidth();           //v1 upperLeft
                drawV1y = moveZoom(rect.yArrayPtr[(4*i)],0) * drawInputHeight;
                drawV2x = moveZoom(rect.xArrayPtr[(4*i)+1],1) * getWidth();         //v2 upperRight
                drawV2y = moveZoom(rect.yArrayPtr[(4*i)+1],0) * drawInputHeight;
                drawV3x = moveZoom(rect.xArrayPtr[(4*i)+2],1) * getWidth();         //v3 bottomRight
                drawV3y = moveZoom(rect.yArrayPtr[(4*i)+2],0) * drawInputHeight;
                drawV4x = moveZoom(rect.xArrayPtr[(4*i)+3],1) * getWidth();         //v4 bottmLeft
                drawV4y = moveZoom(rect.yArrayPtr[(4*i)+3],0) * drawInputHeight;
            }
            else
            {
                drawV1x = moveZoom(rect.xArrayOutPtr[(4*i)],1) * getWidth();
                drawV1y = moveZoom(rect.yArrayOutPtr[(4*i)],0) * drawOutputHeight;
                drawV2x = moveZoom(rect.xArrayOutPtr[(4*i)+1],1) * getWidth();
                drawV2y = moveZoom(rect.yArrayOutPtr[(4*i)+1],0) * drawOutputHeight;
                drawV3x = moveZoom(rect.xArrayOutPtr[(4*i)+2],1) * getWidth();
                drawV3y = moveZoom(rect.yArrayOutPtr[(4*i)+2],0) * drawOutputHeight;
                drawV4x = moveZoom(rect.xArrayOutPtr[(4*i)+3],1) * getWidth();
                drawV4y = moveZoom(rect.yArrayOutPtr[(4*i)+3],0) * drawOutputHeight;
            }

            // paint every slice as a path with a diffirent hue
            Path path;
            path.startNewSubPath (Point<float>(drawV1x ,drawV1y));
            path.lineTo (Point<float>(drawV2x ,drawV2y));
            path.lineTo (Point<float>(drawV3x ,drawV3y));
            path.lineTo (Point<float>(drawV4x ,drawV4y));
            path.closeSubPath();
            g.setColour(arenaTopGrey);
            g.fillPath (path);
            
            // paint an outline and a cross over the slices
            Path stroke;
            stroke.startNewSubPath (Point<float>(drawV1x, drawV1y));
            stroke.lineTo (Point<float>(drawV3x ,drawV3y));
            stroke.lineTo (Point<float>(drawV2x ,drawV2y));
            stroke.lineTo (Point<float>(drawV4x ,drawV4y));
            stroke.closeSubPath();

            // g.setColour(Colour::fromHSV(1., 1., 0., sliceOpacity));
            g.setColour(arenaBrightGreen.withAlpha(0.5f));
            g.strokePath(path, PathStrokeType(1.));
            g.strokePath(stroke, PathStrokeType(1.));
            
            // create text rect
            // paint the black backslice
            float textWidth = 2.f;
            float textHeight = 20.f;
            
            Rectangle<float> topslice
            (path.getBounds().getX() + path.getBounds().getWidth() / (textWidth * 2.f),
             path.getBounds().getY()+path.getBounds().getHeight() / 2.f - (textHeight * 0.75f),
             path.getBounds().getWidth() - path.getBounds().getWidth() / textWidth,
             textHeight);

            Rectangle<float> midslice
            (path.getBounds().getX() + path.getBounds().getWidth() / (textWidth * 2.f),
             path.getBounds().getY()+path.getBounds().getHeight() / 2.f - (textHeight * 0.75f) + 10.f,
             path.getBounds().getWidth() - path.getBounds().getWidth() / textWidth,
             textHeight);
                        
            if (path.getBounds().getHeight() > (textHeight + 15.f))
            {
                g.setColour(arenaBottomGrey);
                g.fillRect(topslice);
                g.fillRect(midslice);
                
                // paint the text overlay
                g.setFont (textHeight/2);
                String name = rect.sliceNameArray[i];
                g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, sliceOpacity*1.666666));
                g.drawText(name, topslice, Justification::centred);
                
                g.setFont (textHeight/2);
                String size = "W: " + to_string(SliceWidth) + " H: " + to_string(SliceHeight);
                g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, sliceOpacity*1.666666));
                g.drawText(size, midslice, Justification::centred);
            }
            
            /*
            String info = "extra info";
            g.drawText(info, textSlice, Justification::centredBottom);
             */

            // end of sliceloop
        }
        // draw a workfield dashed outline
        g.setColour(arenaLessGreen);
        PathStrokeType pathStrokeType(1.f);
        float dashedLength[2];
        dashedLength[0]=4;
        dashedLength[1]=4;
        pathStrokeType.createDashedStroke(compEdge, compEdge, dashedLength, 2);
        g.strokePath(compEdge, pathStrokeType);
        
        // draw a nice black background for the buttons
        // (0, 0, 180+1, 40);
        g.setColour(Colour::fromRGBA(24, 25, 25, 230));
        g.fillRoundedRectangle(-2, -2, 186, 127, 6);
        
        // incdec index label
        // 60+1, 80+2, 60, 40
        g.setColour(arenaTopGrey);
        g.fillRoundedRectangle(123, 83, 57, 38, 4);
        g.setColour(Colours::white);
        g.setFont(16.f);
        String incDecLabel;
        if (currentScreen > 0)
            incDecLabel = to_string(currentScreen);
        else if (currentScreen == 0)
            incDecLabel = "All";
        g.drawText(incDecLabel, 123, 83, 57, 38, Justification::centred);
    }
    // if an older version of resolume is detected don't draw anything but display this splashscreen
    else
    {
        g.setColour(Colours::darkorange);
        g.fillRect(0, 0, getWidth(), getHeight());
        String drawWarningText =
        "THIS SCREEN SETUP WAS MADE WITH AN OLDER VERSION OF RESOLUME AND THEREFORE CAN'T DISPLAY THE SLICES CORRECTLY, PLEASE USE THE LATEST VERSION";
        g.setColour(Colours::black);
        g.setFont(20.f);
        g.setFont (Font("Avenir Next", 30.f, Font::bold));
        g.drawMultiLineText(drawWarningText, getWidth()/4, getHeight()/3, getHeight());
    }
}


void MainComponent::resized()
{
    mouseInputLabel1.setJustificationType(Justification::centred);
    mouseInputLabel1.setBounds(getWidth()/4, getHeight()/2, getWidth(), 40.f);
    mouseInputLabel2.setJustificationType(Justification::centred);
    mouseInputLabel2.setBounds(getWidth()/8, getHeight()/2, getWidth(), 40.f);
    sourceDistanceLabel.setJustificationType(Justification::centred);
    sourceDistanceLabel.setBounds(getWidth()/8, getHeight()/2+30, getWidth(), 40.f);
}


