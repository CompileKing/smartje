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
public Button::Listener,
public Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    virtual void sliderValueChanged (Slider* slider) override
    {
        
    }
    
    void filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged) override
    {
        if (fileComponentThatHasChanged == fileComp.get())
            readFile(fileComp->getCurrentFile());
    }
    
    //what happends when a file gets read
    void readFile(const File& fileToRead)
    {
        
        if (!fileToRead.existsAsFile())
            return;
        
        auto fileText = fileToRead.loadFileAsString();
        auto filePath = fileToRead.getFullPathName();
        rect.getInputRect(filePath.toStdString()); // send the string to InputRect class
        sourceDistance = 1.f;
        sliceOffset = 0;
        sliceMax = rect.sIndex;
        currentScreen = 1;
        wrongResolumeVersion(rect.olderResVersionDetected);
        
        // get the right aspect ratio for the input map
        float compWidth = rect.compResX;
        float compHeight = rect.compResY;
        currentInputWidth = compWidth;
        currentInputHeight = compHeight;
        
        drawInputHeight = getWidth() * (compHeight / compWidth);
        
        resetCamera();
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
    
    void wrongResolumeVersion(bool olderResolume)
    {
        if (olderResolume == true)
        {
            button1.setVisible(0);
            button2.setVisible(0);
            dec.setVisible(0);
            inc.setVisible(0);
        }
        else if (olderResolume == false)
        {
            button1.setVisible(1);
            button2.setVisible(1);
            dec.setVisible(1);
            inc.setVisible(1);
        }
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
            button1.setColour(TextButton::buttonColourId, arenaLessGreen);
            button2.setColour(TextButton::buttonColourId, arenaTopGrey);
        }
        // outputMap button functionality
        if (button == &button2)
        {
            drawInputMap = false;
            sliceOffset = 0;
            sliceMax = rect.screenIndexArray[0];
            button2.setColour(TextButton::buttonColourId, arenaLessGreen);
            button1.setColour(TextButton::buttonColourId, arenaTopGrey);
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

        // get the right aspect ratio for the output map (if there is one)
        if (currentScreen > 0)
        {
            getOutputScreenResolution(currentScreen);
            drawOutputHeight =
            getWidth() * (outputScreenResolutionArray[1]/outputScreenResolutionArray[0]);
        }
        else
            drawOutputHeight = getWidth() * 0.5625;
        
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
    
    void getOutputScreenResolution(int index)
    {
        float screenResX = rect.screenWidthArray[index-1];
        float screenResY = rect.screenHeightArray[index-1];
        outputScreenResolutionArray[0] = screenResX;
        outputScreenResolutionArray[1] = screenResY;
        currentOutputWidth = screenResX;
        currentOutputHeight = screenResY;
    }
    
    float clipFloat(float input, float max)
    {
        float output = 0;
        if (input < max)
        {
            return input;
        }
        else
        {
            return max;
        }
        return output;
    }
    

    //=============================================================================
    //                              everyThing Camera
    //=============================================================================
    
    void mouseDown (const MouseEvent& e) override
    {
        currentMousePosition.setXY(e.getScreenX(), e.getScreenY());

    }
    
    void mouseDoubleClick (const MouseEvent& e) override
    {
        cout << "doubleClick!" << endl;
        resetCamera();
        repaint();
    }
    
    float moveZoom(float inputVector, bool x)
    {
        float moveZoomX = (((inputVector + moveX ) * sourceDistance)*0.5f+0.5f);
        float moveZoomY = (((inputVector + moveY ) * sourceDistance)*0.5f+0.5f);
        float returnValue = 0;
        if (x)
            returnValue = moveZoomX;
        else if (!x)
            returnValue = moveZoomY;
        return returnValue;
    }
        
    void mouseDrag (const MouseEvent& e) override
    {
        mouseIsDragging = true;
        auto* t = getTrail (e.source);
        
        if (t == nullptr)
        {
            t = new Trail (e.source);
            t->path.startNewSubPath (e.position);
            trails.add (t);
        }

        t->pushPoint (e.position, e.mods, e.pressure, e.getDistanceFromDragStartX(),e.getDistanceFromDragStartY());
                
        if (fingers == 1)
        {
            // calculate pinch zooom
            mouseClickCounter++;
            for (auto* trail : trails)
            {
                if (getIndex(*trail) == 0)
                {
                    deltaPosition0 = getDragStart(*trail);
                    position0 = getPosition(*trail);
                }
                if (getIndex(*trail) == 1)
                {
                    deltaPosition1 = getDragStart(*trail);
                    position1 = getPosition(*trail);
                }
                
                if (position0.getX() > position1.getX())
                {
                    deltaPosition1.setX(deltaPosition1.getX()*-1.f);
                }
                else if (position0.getX() < position1.getX())
                {
                    deltaPosition0.setX(deltaPosition0.getX()*-1.f);
                }
                
                sourceDistance = abs(addToZoom((deltaPosition0.getX() + deltaPosition1.getX()) / 5000.f));
                
                if (sourceDistance < 0.4f) // make sure the user can't zoom out all the way
                    zoomAmt = 0.4f;
            }
        }

        if (fingers == 0)
        {
            deltaX = e.getDistanceFromDragStartX();
            deltaY = e.getDistanceFromDragStartY();
            moveX = addToMoveX(deltaX)/4000.f;
            moveY = addToMoveY(deltaY)/4000.f;
        }
        repaint();
    }
    
    void resetCamera ()
    {
        moveAmtX = 0.f;
        moveAmtY = 0.f;
        zoomAmt = 0.7f;
        sourceDistance = 0.7f;
        moveX = 0;
        moveY = 0;
    }
    
    float getDelta (float amt)
    {
        float value = amt;
        static float oldValue = value;
        value = value - oldValue;
        return static_cast<float>(value);
        oldValue = value;
    }
    
    float addToMoveX (float amt)
    {
        moveAmtX += amt;
        return static_cast<float>(moveAmtX);
    }
    
    float addToMoveY (float amt)
    {
        moveAmtY += amt;
        return static_cast<float>(moveAmtY);
    }
    
    float addToZoom (float amt)
    {
            zoomAmt += amt;
            return static_cast<float>(zoomAmt);
    }
        
    void mouseUp (const MouseEvent& e) override
    {
        trails.removeObject (getTrail (e.source));
        repaint();
        fingers = 0;
        mouseClickCounter = 0;
        mouseIsDragging = false;        
    }
    
    struct Trail
    {
        Trail (const MouseInputSource& ms)
        : source (ms)
        {}
        
        void pushPoint (Point<float> newPoint, ModifierKeys newMods, float pressure, int dragDistanceX, int dragDistanceY)
        {
            dragStart.setX(dragDistanceX);
            dragStart.setY(dragDistanceY);
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
        Point<float> lastPoint, currentPosition, dragStart;
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
    
    Point<float> getDragStart(Trail& trail)
    {
        return trail.dragStart;
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
    
    void printSliceInfo ()
    {
        cout << sliceNameString << endl <<
        sliceXString << endl <<
        sliceYString << endl <<
        sliceLeftString << endl <<
        sliceTopString << endl <<
        sliceWidthString << endl <<
        sliceHeightString << endl <<
        sliceRotationString << endl <<
        sliceEnabledString << endl <<
        endl << "/////////" <<
        endl << endl;;
    }
    
private:
    //==============================================================================
    // Your private member variables go here...
    
    InputRect rect;
    
    Point<float> position0;
    Point<float> position1;
    Point<float> deltaPosition0;
    Point<float> deltaPosition1;
    
    
    float sourceDistance = 0.f;
    float sliceOpacity = 0.f;
    int fingers = 0;
    int mouseClickCounter;
    
    float outputScreenResolutionArray[2];
    
    float moveX = 0;
    float moveY = 0;
    float deltaX = 0.f;
    float deltaY = 0.f;
    
    double moveAmtX = 0.f;
    double moveAmtY = 0.f;
    double zoomAmt = 1.f;

    float drawV1x;
    float drawV2x;
    float drawV3x;
    float drawV4x;
    
    float drawV1y;
    float drawV2y;
    float drawV3y;
    float drawV4y;
    
    float drawInputHeight;
    float drawOutputHeight;
    int currentInputWidth;
    int currentInputHeight;
    int currentOutputWidth;
    int currentOutputHeight;
    Point<float> currentMousePosition;
    
    int currentScreen = 0;
    int sliceOffset;
    int sliceMax;
    
    int sliceWidth;
    int sliceHeight;
    
    TextButton button1;
    TextButton button2;
    TextButton inc;
    TextButton dec;
    
    LookAndFeel_V4 arenaLAF;
    Colour arenaBrightGreen = Colour::fromRGB(133,254,211);
    Colour arenaLessGreen = Colour::fromRGB(79, 139, 117);
    Colour arenaLessPink = Colour::fromRGB(145,84,144);
    Colour arenaTopGrey = Colour::fromRGB(58,58,57);
    Colour arenaMidGrey = Colour::fromRGB(42,42,42);
    Colour arenaBottomGrey = Colour::fromRGB(25,25,25);
    
    String sliceNameString;
    String sliceXString;
    String sliceYString;
    String sliceLeftString;
    String sliceTopString;
    String sliceWidthString;
    String sliceHeightString;
    String sliceRotationString;
    String sliceEnabledString;

    bool mouseIsDragging = false;
    bool drawInputMap = true;
    bool sliceIsSelected = false;

    unique_ptr<FilenameComponent> fileComp;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
