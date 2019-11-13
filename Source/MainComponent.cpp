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
    fileComp->setBounds (-126, 0, 180+1, 40);
    fileComp->setLookAndFeel(&arenaLAF);
        
    addAndMakeVisible(button1);
    button1.setVisible(1);
    button1.setButtonText("Input");
    button1.setBounds   (fileComp->getBounds().getRight(), 0, 90, 40);
    cout << "fileCompRight: " << fileComp->getBounds().getRight() << endl;
    button1.addListener(this);
    button1.setLookAndFeel(&arenaLAF);

    addAndMakeVisible(button2);
    button2.setVisible(1);
    button2.setButtonText("Output");
    button2.setBounds   (button1.getBounds().getRight(),0,90,40);
    button2.addListener(this);
    button2.setLookAndFeel(&arenaLAF);
    
    button1.setColour(TextButton::buttonColourId, arenaLessGreen);
    button2.setColour(TextButton::buttonColourId, arenaTopGrey);
    
    addAndMakeVisible(inc);
    inc.setVisible(1);
    inc.setButtonText(">");
    inc.setBounds       (0, 80+2, 55, 40);
//    dec.setBounds       (0, 80+2, 55, 40);
    inc.addListener(this);
    inc.setLookAndFeel(&arenaLAF);
    
    addAndMakeVisible(dec);
    dec.setVisible(1);
    dec.setButtonText("<");
    dec.setBounds       (0, inc.getBounds().getBottom(), 55, 40);
//    inc.setBounds       (60+1, 80+2, 55, 40);
    dec.addListener(this);
    dec.setLookAndFeel(&arenaLAF);
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

    // for every slice
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
                    sliceWidth = raw.getBounds().getWidth();
                    sliceHeight = raw.getBounds().getHeight();
                }
                
                else
                {
                    raw.applyTransform(AffineTransform::rotation(-rect.outputSliceRotationArray[i], center.x, center.y ));
                    sliceWidth = raw.getBounds().getWidth();
                    sliceHeight = raw.getBounds().getHeight();
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
            g.setColour(arenaTopGrey.withAlpha(sliceOpacity));
            g.fillPath (path);
            
            // paint an outline and a cross over the slices
            Path cross;
            cross.startNewSubPath (Point<float>(drawV1x, drawV1y));
            cross.lineTo (Point<float>(drawV3x ,drawV3y));
            cross.lineTo (Point<float>(drawV2x ,drawV2y));
            cross.lineTo (Point<float>(drawV4x ,drawV4y));
            cross.closeSubPath();
            
            // check for mouseclicks in bounds
            g.setColour(arenaLessGreen.withAlpha(sliceOpacity));
            if (!mouseIsDragging)
            {
                if (path.contains(currentMousePosition.getX(), currentMousePosition.getY()))
                {
                    sliceIsSelected = true;
                    g.setColour(Colours::orange.withAlpha(0.2f));
                    g.fillPath(path);
                    g.setColour(Colours::orange.withAlpha(0.6f));
                    sliceNameString = rect.sliceNameArray[i];
                    sliceWidthString = "Width: " + to_string(sliceWidth);
                    sliceHeightString = "Height: " + to_string(sliceHeight);
                    sliceEnabledString = "Enabled: " + to_string(rect.sliceEnabledArray[i]);
                    
                }
                else
                    sliceIsSelected = false;
            }
                    
            g.strokePath(path, PathStrokeType(1.));
            g.strokePath(cross, PathStrokeType(1.));
            
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
                g.setColour(arenaBottomGrey.withAlpha(sliceOpacity));
                g.fillRect(topslice);
                g.fillRect(midslice);
                // paint the text overlay
                g.setFont (textHeight/2);
                String name = rect.sliceNameArray[i];
                g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, sliceOpacity*1.666666));
                g.drawText(name, topslice, Justification::centred);
                
                g.setFont (textHeight/2);
                String size = "W: " + to_string(sliceWidth) + " H: " + to_string(sliceHeight);
                g.setColour(Colour::fromFloatRGBA(1.f, 1.f, 1.f, sliceOpacity*1.666666));
                g.drawText(size, midslice, Justification::centred);
            }
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
        g.setColour(Colour::fromRGBA(24, 25, 25, 230));
        g.fillRoundedRectangle(0, 0, 55+2, dec.getBounds().getBottom()+2, 6);
        g.fillRoundedRectangle(0, 0, button2.getBounds().getRight()+2, 40+2, 6);
        
        // incdec index label
        if (currentScreen > 0)
            g.setColour(arenaLessGreen);
        else
            g.setColour(arenaTopGrey);
        g.fillRoundedRectangle(2, 41, 52, 40, 4);
        g.setColour(Colours::white);
        g.setFont(16.f);
        String incDecLabel;
        if (currentScreen > 0)
            incDecLabel = to_string(currentScreen);
        else if (currentScreen == 0)
            incDecLabel = "All";
        g.drawText(incDecLabel, 2, 41, 50, 40, Justification::centred);
        
        // draw screen / comp info
        g.setColour(arenaBottomGrey.withAlpha(0.5f));
        Rectangle<float> screenInfoBackRect
        (fileComp->getRight(),
         button1.getBottom(),
         button1.getWidth(),
         button1.getHeight());
        g.fillRoundedRectangle(screenInfoBackRect, 4);
                        
        String compScreenInfo = "";
        String topText;
        
        if (currentScreen > 0)
            topText = rect.screenNameArray[currentScreen-1];
        else
            topText = "All Screens";
                
        if (drawInputMap)
            compScreenInfo = to_string(currentInputWidth) + "  " + to_string(currentInputHeight);
        else
        {
            if (currentScreen > 0)
                compScreenInfo = to_string(currentOutputWidth) + "  " + to_string(currentOutputHeight);
            else
                compScreenInfo = " .. ";
        }

        g.setColour(arenaBrightGreen);
        g.setFont(10.f);
        
        g.drawText
        (topText,
         fileComp->getBounds().getRight(),
         button1.getBottom()-10.f,
         90,
         40,
         Justification::centred);
        g.setColour(Colours::white);
        g.setFont(15.f);
        g.drawText
        (compScreenInfo,
         fileComp->getBounds().getRight(),
         button1.getBottom()+5,
         90,
         40,
         Justification::centred);
        
        // draw slice info
        if (!mouseIsDragging)
        {
            printSliceInfo();
            int sliceInfoWidth = 95;
            int sliceInfoHeight = 150;
            int textHeight = 13;
            int textHeightOffset = 20;
            g.setColour(arenaBottomGrey.withAlpha(0.9f));
            Rectangle<float> sliceInfoRect (0, getHeight()-sliceInfoHeight, sliceInfoWidth, sliceInfoHeight);
            g.fillRoundedRectangle(sliceInfoRect, 4.f);
            g.drawRoundedRectangle(sliceInfoRect, 4.f, 2.f);
            g.setColour(Colours::orange);
            g.setFont(15.f);
            g.drawText(sliceNameString,
                       0, getHeight()-sliceInfoHeight - (sliceInfoHeight / 2.f) + textHeightOffset , sliceInfoWidth, sliceInfoHeight, Justification::centred);
            g.setColour(Colours::white);
            g.setFont(textHeight);
            g.drawText(sliceWidthString,
                       0, getHeight()-sliceInfoHeight - (sliceInfoHeight / 2.f) + textHeightOffset + textHeightOffset , sliceInfoWidth, sliceInfoHeight, Justification::centred);
            g.drawText(sliceHeightString,
                       0, getHeight()-sliceInfoHeight - (sliceInfoHeight / 2.f) + textHeightOffset * 2.f + textHeightOffset , sliceInfoWidth, sliceInfoHeight, Justification::centred);
        }
        
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

}


