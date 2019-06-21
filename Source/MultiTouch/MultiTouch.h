/*
  ==============================================================================

    MultiTouch.h
    Created: 21 Jun 2019 4:58:45pm
    Author:  Sem Shimla

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class MultiTouchDemo    : public Component
{
public:
    MultiTouchDemo()
    {
        setOpaque (true);
        
        setSize (500, 500);
    }
    
    void paint (Graphics& g) override
    {
        
        g.setFont (14.0f);
        g.drawFittedText ("Drag here with as many fingers as you have!",
                          getLocalBounds().reduced (30), Justification::centred, 4);
        
        for (auto* trail : trails)
            drawTrail (*trail, g);
    }
    
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
            
            if (lastPoint.getDistanceFrom (newPoint) > 5.0f)
            {
                if (lastPoint != Point<float>())
                {
                    Path newSegment;
                    newSegment.startNewSubPath (lastPoint);
                    newSegment.lineTo (newPoint);
                    
                    auto diameter = 20.0f * (pressure > 0 && pressure < 1.0f ? pressure : 1.0f);
                    
                    PathStrokeType (diameter, PathStrokeType::curved, PathStrokeType::rounded).createStrokedPath (newSegment, newSegment);
                    path.addPath (newSegment);
                }
                
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
        
        if (trail.modifierKeys.isCommandDown()) desc << " (CMD)";
        if (trail.modifierKeys.isShiftDown())   desc << " (SHIFT)";
        if (trail.modifierKeys.isCtrlDown())    desc << " (CTRL)";
        if (trail.modifierKeys.isAltDown())     desc << " (ALT)";
        
        g.drawText (desc,
                    Rectangle<int> ((int) trail.currentPosition.x - 200,
                                    (int) trail.currentPosition.y - 60,
                                    400, 20),
                    Justification::centredTop, false);
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
};


