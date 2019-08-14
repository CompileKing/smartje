/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReadConvertAss/ReadConvertAss.h"


using namespace std;

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainComponent   : public Component,
public FilenameComponentListener,
public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged) override
    {
        if (fileComponentThatHasChanged == fileComp.get())
            readFile(fileComp->getCurrentFile());
    }

    //what happends when a file gets read
    void readFile(const File& fileToRead)
    {
        button1.setVisible(1);
        button2.setVisible(1);
        dec.setVisible(1);
        inc.setVisible(1);
        if (!fileToRead.existsAsFile())
            return;
        
        auto fileText = fileToRead.loadFileAsString();
        auto filePath = fileToRead.getFullPathName();
        rect.getInputRect(filePath.toStdString()); // send the string to InputRect class
        sourceDistance = (getWidth()/10);
        sliceOffset = 0;
        sliceMax = rect.sIndex;
        
        currentScreen = 0;

        repaint();
        
        cout << endl;
        cout << "screenIndexArray: " << endl;
        for (int i=0;i<8;i++)
        {
            cout << rect.screenIndexArray[i];
        }
        cout << endl;
        cout << "screenIndex: " << rect.screenIndex << endl;
    }
    
    // button functionality
    void buttonClicked (Button* button) override
    {
        // inputMap button functionality
        if (button == &button1)
        {
            drawInputMap = true;
            sliceOffset = 0;
            sliceMax = rect.sIndex;
        }
        // outputMap button functionality
        if (button == &button2)
        {
            drawInputMap = false;
            sliceOffset = 0;
            sliceMax = rect.screenIndexArray[0];
        }
        // inc button functionality
        if (currentScreen < rect.screenIndex)
        {
            if (button == &inc)
            {
                currentScreen++;
            }
        // dec button functionality
        }
        if (currentScreen > 0)
        {
            if (button == &dec)
            {
                currentScreen--;
            }
        }
        selectScreen(currentScreen);
        repaint();

    }
    // screen selection function
    void selectScreen (int index)
    {
        if (index > 0)
        {
            int sum = 0;
            for (int i=0;i<index;i++)
            {
                sum += rect.screenIndexArray[i-1];
            }
            sliceOffset = sum;
            sliceMax = rect.screenIndexArray[index-1] + sum;
        }
        if (index == 0)
        {
            sliceOffset = 0;
            sliceMax = rect.sIndex;
        }
    }

    //=============================================================================
    //                              multiTouchDemoStuff
    //=============================================================================
    
    
    void mouseDrag (const MouseEvent& e) override
    {
        auto* t = getTrail (e.source);
        
        if (t == nullptr)
        {
            t = new Trail (e.source);
            t->path.startNewSubPath (e.position);
            trails.add (t);
        }

        t->pushPoint (e.position, e.mods, e.pressure);
        
        if (fingers == 1)
        {
            for (auto* trail : trails) // get distance for 2 fingers
            {
                if (getIndex(*trail) == 0)
                {
                    position0 = getPosition(*trail);
                }
                if (getIndex(*trail) == 1)
                {
                    position1 = getPosition(*trail);
                }
                sourceDistance = abs(position0.getDistanceFrom(position1)-60);
            }
        }
        
        if (fingers == 0)
        {
            float xPos = e.getPosition().x;
            float yPos = e.getPosition().y;
            moveX = ((xPos/getWidth()*2.f-1.f)*8.f)*(sourceDistance/getWidth()*-1.f)*0.5;
            moveY = ((yPos/getHeight()*2.f-1.f)*8.f)*(sourceDistance/getWidth()*-1.f)*0.5;
            
//            cout << "moveX: " << moveX << " moveY: " << moveY << endl;
        }
        repaint();
    }
    
    
    void mouseUp (const MouseEvent& e) override
    {
        trails.removeObject (getTrail (e.source));
        repaint();
        fingers = 0;
        oldZoom = zoomInOut;
    }
    
    struct Trail
    {
        Trail (const MouseInputSource& ms)
        : source (ms)
        {}
        
        void pushPoint (Point<float> newPoint, ModifierKeys newMods, float pressure)
        {
            currentPosition = newPoint;
            modifierKeys = newMods;
            
            if (lastPoint.getDistanceFrom (newPoint) > 1.0f)
            {
                lastPoint = newPoint;
            }
        }
        
        MouseInputSource source;
        Path path;
        Colour colour  { Colour::fromHSV(1.f, 1.f, 0.5f, 0.5f) };
        Point<float> lastPoint, currentPosition;
        ModifierKeys modifierKeys;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Trail)
    };
    
    OwnedArray<Trail> trails;
    
    
    int getIndex(Trail& trail)
    {
        int currentIndex = 0;
        currentIndex = trail.source.getIndex();
        return currentIndex;
    }
    
    Point<float> getPosition(Trail& trail)
    {
        return trail.currentPosition;
    }
    
    Trail* getTrail (const MouseInputSource& source)
    {
        for (auto* trail : trails)
        {
            if (trail->source == source)
            {
                return trail;
            }
            else fingers = 1;
        }
        return nullptr;
    }
    
private:
    //==============================================================================
    // Your private member variables go here...
    
    InputRect rect;
    
    Point<float> position0;
    Point<float> position1;
    float sourceDistance = 0.f;
    float sliceOpacity = 0.f;
    int fingers = 0;
    
    float moveX = 0;
    float moveY = 0;

    float zoomInOut;
    float oldZoom;
    float lastZoomFrame;
    
    float drawV1x;
    float drawV2x;
    float drawV3x;
    float drawV4x;
    
    float drawV1y;
    float drawV2y;
    float drawV3y;
    float drawV4y;
    
    float drawTheRightHeight;
    float drawTheNormalHeight;
    
    int currentScreen = 0;
    int sliceOffset;
    int sliceMax;
    
    TextButton button1;
    TextButton button2;
    
    TextButton inc;
    TextButton dec;
    
    
    bool drawInputMap = true;

    unique_ptr<FilenameComponent> fileComp;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
