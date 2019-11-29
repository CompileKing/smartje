/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    startTimer(30);
    checkDocumentsFolder();
//    12.9
//    2732 x 2048
    int screenSizeX = 2732 / 2;
    int screenSizeY = 2048 / 2;
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
                                         "*.xml",                       // browser wildcard suffix,
                                         {},                       // enforced suffix,
                                         "Open File"));  // text when nothing selected
    addAndMakeVisible(fileComp.get());
    fileComp->addListener(this);
    fileComp->setBounds (-126, 0, 180+1, 40);
    fileComp->setLookAndFeel(&arenaLAF);
    
    addAndMakeVisible(sliceColourButton);
    sliceColourButton.setBounds(fileComp->getRight(), 0, 55, 40);
    sliceColourButton.setButtonText("Col");
    sliceColourButton.setLookAndFeel(&arenaLAF);
    sliceColourButton.addListener(this);
    sliceColourButton.setImages(false, true, true, colImageOff, 1.f, Colours::orange.withAlpha(0.f), colImageOff, 1.f, Colours::white.withAlpha(0.f), colImageOff, 0.5f, Colours::white.withAlpha(0.f));
    
    addAndMakeVisible(button1);
    button1.setButtonText("Input");
    button1.setBounds   (sliceColourButton.getRight(), 0, 90, 40);
    button1.addListener(this);
    button1.setLookAndFeel(&arenaLAF);
    
    addAndMakeVisible(button2);
    button2.setButtonText("Output");
    button2.setBounds   (button1.getBounds().getRight(),0,90,40);
    button2.addListener(this);
    button2.setLookAndFeel(&arenaLAF);
    
    button1.setColour(TextButton::buttonColourId, arenaLessGreen);
    button2.setColour(TextButton::buttonColourId, arenaTopGrey);

    addAndMakeVisible(inc);
    inc.setButtonText("");
    inc.setBounds       (0+1, 80+2, 55, 40);
    inc.addListener(this);
    inc.setLookAndFeel(&arenaLAF);
    inc.setImages(false, true, true, incImage, 1.f, Colours::orange.withAlpha(0.f), incImage, 1.f, Colours::white.withAlpha(0.f), incImage, 0.5f, Colours::white.withAlpha(0.f));
    
    
    addAndMakeVisible(dec);
    dec.setButtonText("");
    dec.setBounds       (0+1, inc.getBounds().getBottom(), 55, 40);
    dec.addListener(this);
    dec.setLookAndFeel(&arenaLAF);
    dec.setImages(false, true, true, decImage, 1.f, Colours::orange.withAlpha(0.f), decImage, 1.f, Colours::white.withAlpha(0.f), decImage, 0.5f, Colours::white.withAlpha(0.f));
}


MainComponent::~MainComponent()
{
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{
    sliceSelectedArray.clear();
    
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
                sliceLeft = raw.getBounds().getTopLeft().getX();
                sliceTop = raw.getBounds().getTopLeft().getY();
            }
            
            else
            {
                raw.applyTransform(AffineTransform::rotation(-rect.outputSliceRotationArray[i], center.x, center.y ));
                sliceWidth = raw.getBounds().getWidth();
                sliceHeight = raw.getBounds().getHeight();
                sliceLeft = raw.getBounds().getTopLeft().getX();
                sliceTop = raw.getBounds().getTopLeft().getY();
            }
        }
        
        // prepare slice colour hue offset
        float sliceMaxFloat = sliceMax - sliceOffset;
        float hueOffset = 1.f / sliceMaxFloat;
        float relativeSliceIndex = i - sliceOffset;
        float currentSliceHue = relativeSliceIndex * hueOffset;
        Colour currentSliceColour = Colour::fromHSV(currentSliceHue, 1.f, 1.f, 0.8f);
                
        if (rect.sliceEnabledArray[i] == 1)
            sliceOpacity = 0.9f;
        else
            sliceOpacity = 0.1f;

        // create drawable slices from xml
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
        
        // paint every slice as a path
        Path path;
        path.startNewSubPath (Point<float>(drawV1x ,drawV1y));
        path.lineTo (Point<float>(drawV2x ,drawV2y));
        path.lineTo (Point<float>(drawV3x ,drawV3y));
        path.lineTo (Point<float>(drawV4x ,drawV4y));
        path.closeSubPath();
        
        if (drawSliceColours)
            g.setColour(currentSliceColour.withAlpha(sliceOpacity));
        else
            g.setColour(arenaTopGrey.withAlpha(sliceOpacity));
        g.fillPath (path);
        
        // paint an outline and a cross over the slices
        Path cross;
        cross.startNewSubPath (Point<float>(drawV1x, drawV1y));
        cross.lineTo (Point<float>(drawV3x ,drawV3y));
        cross.lineTo (Point<float>(drawV2x ,drawV2y));
        cross.lineTo (Point<float>(drawV4x ,drawV4y));
        cross.closeSubPath();
        
        // slice colour switch
        if (drawSliceColours)
            g.setColour(arenaBottomGrey.withAlpha(sliceOpacity));
        else
            g.setColour(arenaLessGreen.withAlpha(sliceOpacity));
        
        // slice selection
        if (!mouseIsDragging)
        {
            if (rect.sliceEnabledArray[i] == 1)
            {
                if (path.contains(currentMousePosition.getX(), currentMousePosition.getY()))
                {
                    sliceIsSelected = true;
                    sliceSelectedArray.add(sliceIsSelected);
                    g.setColour(Colours::orange.withAlpha(0.9f));
                    g.fillPath(path);
                    g.setColour(Colours::orange.withAlpha(0.6f));
                    sliceNameString = rect.sliceNameArray[i];
                    sliceXString = "X: " + to_string(raw.getBounds().getCentreX());
                    sliceYString = "Y: " + to_string(raw.getBounds().getCentreY());
                    if (drawInputMap)
                    {
                        sliceRotationString = "Rot: " + to_string(rect.inputSliceRotationArray[i] / 3.14159f * 180.f);
                        if (rect.inputSliceRotationArray[i] == 0)
                        {
                            sliceLeftString = "Left: " + to_string(sliceLeft);
                            sliceTopString = "Top: " + to_string(sliceTop);
                        }
                        else
                        {
                            sliceLeftString = "Left: N/A     ";
                            sliceTopString  = "Top: N/A     ";
                        }
                    }
                    else
                    {
                        sliceRotationString = "Rot: " + to_string(rect.outputSliceRotationArray[i] / 3.14159f * 180.f);
                        if (rect.outputSliceRotationArray[i] == 0)
                        {
                            sliceLeftString = "Left: " + to_string(sliceLeft);
                            sliceTopString = "Top: " + to_string(sliceTop);
                        }
                        else
                        {
                            sliceLeftString = "Left: N/A     ";
                            sliceTopString  = "Top: N/A     ";
                        }
                    }
                    sliceWidthString = "Width: " + to_string(raw.getBounds().getWidth());
                    sliceHeightString = "Height: " + to_string(raw.getBounds().getHeight());
                    sliceEnabledString = "Enabled: " + to_string(rect.sliceEnabledArray[i]);
                }
            }
        }
        
        // draw outlines and a cross for each slice
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
    
    // draw a black background for the buttons
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
     sliceColourButton.getWidth() + button1.getWidth(),
     button1.getHeight());
    g.fillRoundedRectangle(screenInfoBackRect, 4);
    
    String compScreenInfo = "";
    String topText;
    
    if (currentScreen > 0)
        topText = rect.screenNameArray[currentScreen-1];
    else
    {
        topText = "All Screens";
    }

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
     fileComp->getBounds().getRight() + 8.f,
     button1.getBottom()-10.f,
     sliceColourButton.getWidth() + button1.getWidth(),
     40,
     Justification::centredLeft);
    g.setColour(Colours::white);
    g.setFont(15.f);
    g.drawText
    (compScreenInfo,
     fileComp->getBounds().getRight() + 8.f,
     button1.getBottom()+5,
     90,
     40,
     Justification::centredLeft);
    
    // draw slice info
    if (sliceSelectedArray.size() > 0)
    {
        if (!mouseIsDragging)
        {
            int sliceInfoWidth = 95;
            int sliceInfoHeight = 150;
            int textHeight = 13;
            int textHeightOffset = 15;
            int textWidthOffset = 5;
            int textOffsetFromTop = -(sliceInfoHeight / 2.f) + textHeight;
            g.setColour(arenaBottomGrey.withAlpha(0.9f));
            Rectangle<float> sliceInfoRect (getWidth()-sliceInfoWidth, 0, sliceInfoWidth, sliceInfoHeight - 17.f);
            g.fillRoundedRectangle(sliceInfoRect, 4.f);
            g.drawRoundedRectangle(sliceInfoRect, 4.f, 2.f);
            g.setColour(Colours::orange);
            g.setFont(15.f);
            g.drawText(sliceNameString,
                       getWidth()- sliceInfoWidth - textWidthOffset,  textHeightOffset * 0.f + textOffsetFromTop, sliceInfoWidth, sliceInfoHeight, Justification::centredRight);
            g.setColour(Colours::white);
            g.setFont(textHeight);
            g.drawText(sliceXString.dropLastCharacters(4),
                       getWidth()- sliceInfoWidth - textWidthOffset,  textHeightOffset * 1.f + textOffsetFromTop, sliceInfoWidth, sliceInfoHeight, Justification::centredRight);
            g.drawText(sliceYString.dropLastCharacters(4),
                       getWidth()- sliceInfoWidth - textWidthOffset,  textHeightOffset * 2.f + textOffsetFromTop, sliceInfoWidth, sliceInfoHeight, Justification::centredRight);
            g.drawText(sliceLeftString.dropLastCharacters(4),
                       getWidth()- sliceInfoWidth - textWidthOffset,  textHeightOffset * 3.f + textOffsetFromTop, sliceInfoWidth, sliceInfoHeight, Justification::centredRight);
            g.drawText(sliceTopString.dropLastCharacters(4),
                       getWidth()- sliceInfoWidth - textWidthOffset,  textHeightOffset * 4.f + textOffsetFromTop, sliceInfoWidth, sliceInfoHeight, Justification::centredRight);
            g.drawText(sliceWidthString.dropLastCharacters(4),
                       getWidth()- sliceInfoWidth - textWidthOffset,  textHeightOffset * 5.f + textOffsetFromTop, sliceInfoWidth, sliceInfoHeight, Justification::centredRight);
            g.drawText(sliceHeightString.dropLastCharacters(4),
                       getWidth()- sliceInfoWidth - textWidthOffset,  textHeightOffset * 6.f + textOffsetFromTop, sliceInfoWidth, sliceInfoHeight, Justification::centredRight);
            g.drawText(sliceRotationString.dropLastCharacters(4),
                       getWidth()- sliceInfoWidth - textWidthOffset,  textHeightOffset * 7.f + textOffsetFromTop, sliceInfoWidth, sliceInfoHeight, Justification::centredRight);
        }
    }
        
    // draw splash screens
    if (ShowSplashScreen)
    {
        hideUIelements(true);
        g.fillAll (arenaBottomGrey);
        createSplashScreenRect();
        switch(splashScreenMouseClickCounter) {
            case 0:
                g.drawImage(beginScreen, splashScreenRect);
                break;
            case 2:
                g.drawImage(splashScreen1, splashScreenRect);
                break;
            case 4:
                g.drawImage(splashScreen2, splashScreenRect);
                break;
            case 6:
                g.drawImage(splashScreen3, splashScreenRect);
                break;
            case 8:
                ShowSplashScreen = false;
                repaint();
                break;
            default:
                ShowSplashScreen = false;
        }
    }
    else if (!ShowSplashScreen)
    {
        if (showUiElementsAfterSplash)
        {
            hideUIelements(false);
            cout << "splashScreenOff" << endl;
            showUiElementsAfterSplash = false;
        }
        if (showFileSplash)
        {
            hideUIelements(true);
            g.fillAll(arenaBottomGrey);
            createSplashScreenRect();
            g.drawImage(fileSplash, splashScreenRect);
        }
        else
            hideUIelements(false);
    }

//    cout << endl;
//    cout << "/////////////////endPaintRound//////////////////////" << endl;
//    cout << endl;
    
}

void MainComponent::resized()
{
    
}


