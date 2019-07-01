/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReadConvertAss/ReadConvertAss.h"
#include "MultiTouch/MultiTouch.h"

using namespace std;

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainComponent   : public Component,
public FilenameComponentListener
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
    
    void readFile(const File& fileToRead)
    {
        if (!fileToRead.existsAsFile()) // [1]
            return;
        
        auto fileText = fileToRead.loadFileAsString();
        auto filePath = fileToRead.getFullPathName();
        rect.getInputRect(filePath.toStdString());
        repaint();
        
        
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
        repaint();
    }
    
    void mouseUp (const MouseEvent& e) override
    {
        trails.removeObject (getTrail (e.source));
        repaint();
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
    
    void drawTrail (Trail& trail, Graphics& g)
    {
        
        g.setColour (trail.colour);
        g.fillPath (trail.path);
        
        auto radius = 40.0f;
        
        g.setColour (Colours::black);
        g.drawEllipse (trail.currentPosition.x - radius,
                       trail.currentPosition.y - radius,
                       radius * 2.0f, radius * 2.0f, 2.0f);
        
        
        g.setFont (14.0f);
        
        String desc ("Mouse #");
        desc << trail.source.getIndex();
        
        
        auto pressure = trail.source.getCurrentPressure();
        
        if (pressure > 0.0f && pressure < 1.0f)
            desc << "  (pressure: " << (int) (pressure * 100.0f) << "%)";
        
        
        g.drawText (desc,
                    Rectangle<int> ((int) trail.currentPosition.x - 200,
                                    (int) trail.currentPosition.y - 60,
                                    400, 20),
                    Justification::centredTop, false);
    }
    
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
                return trail;
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
    
    
    float dragUp;
    
    unique_ptr<FilenameComponent> fileComp;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
