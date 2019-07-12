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
    
    void readFile(const File& fileToRead) //what happends when a file gets read
    {
        if (!fileToRead.existsAsFile())
            return;
        
        auto fileText = fileToRead.loadFileAsString();
        auto filePath = fileToRead.getFullPathName();
        rect.getInputRect(filePath.toStdString());
        sourceDistance = (getWidth()/10);
        repaint();
        
        for (int i =0; i<rect.screenIndex; i++)
        {
            auto* tb = new ToggleButton (rect.screenNameArray[i]);
            
            tb->setRadioGroupId (1234);
            tb->setBounds (10, 50 + i * 22, 180, 22);
            tb->setTooltip ("A set of mutually-exclusive radio buttons");
            
            if (i == 0)
                tb->setToggleState (true, dontSendNotification);
            addAndMakeVisible(tb);
            /*
            cout << "screenName: " << rect.screenNameArray[i] << endl;
            cout << "screenIndexArray: " << rect.screenIndexArray[i] << endl;
             */
        }
    }
    
    void buttonClicked (Button* button) override
    {
        if (button == &button1)
        {
            drawInputMap = true;
        }
        if (button == &button2)
        {
            drawInputMap = false;
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
        //else fingers = 1;
        
        
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
        // cout << "fingers: " << fingers << endl;
        if (fingers == 0)
        {
            float xPos = e.getPosition().x;
            float yPos = e.getPosition().y;
            moveX = ((xPos/getWidth()*2.f-1.f)*3.f)*(sourceDistance/getWidth()*-1.f);
            moveY = ((yPos/getHeight()*2.f-1.f)*3.f)*(sourceDistance/getWidth()*-1.f);
            
//            cout << "moveX: " << moveX << " moveY: " << moveY << endl;
        }
        
        repaint();
    }
    
    
    void mouseUp (const MouseEvent& e) override
    {
        trails.removeObject (getTrail (e.source));
        repaint();
        fingers = 0;
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

    float dragUp;
    
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
    
    TextButton button1;
    TextButton button2;
    
    
    
    bool drawInputMap = true;

    unique_ptr<FilenameComponent> fileComp;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
