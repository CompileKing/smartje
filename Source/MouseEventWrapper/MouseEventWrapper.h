/*
  ==============================================================================

    MouseEventWrapper.h
    Created: 9 Dec 2019 12:03:32pm
    Author:  Sem Shimla

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

    class MouseEventWrapper {
    public:
        const ModifierKeys& mods;

        MouseEventWrapper(const MouseEvent& e, const MouseEvent* last = nullptr);

        Point<int> getMouseDownPosition() const;
        int getDistanceFromDragStartX() const;
        Point<int> getOffsetFromDragStart() const;
        int getMouseDownY() const;

        operator bool() const;
        void operator++(int);

    private:
        int getDeltaX() const;
        int getDeltaY() const;
        int getStepSize() const;
        int getTotalNumIter() const;
        int getOffsetX() const;
        int getOffsetY() const;

        const MouseEvent& _e;
        const MouseEvent* _last;
        int _iterNum;
        int _totalNumIter;
    };
