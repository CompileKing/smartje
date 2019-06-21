/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


int screenSizeX = 1920;
int screenSizeY = 1080;

//==============================================================================
MainComponent::MainComponent()
{
    
    rect.getInputRect();
    setSize (screenSizeX, screenSizeY);
    addMouseListener(this, true);
    
}



MainComponent::~MainComponent()
{
}






void MainComponent::mouseDrag (const MouseEvent& e)
{
    
    // e.position, e.mods, e.pressure
    
    
    clickColour = e.position.y / getHeight() * 5.;
    cout << clickColour << endl;
    repaint();
}

 

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    
    g.fillAll (Colour::fromHSV(0.f, 0.f, 0.2, 1.f));

    for (int i=0;i<rect.sIndex;i++)
    {
        float sliceColor = (i*0.1)/(rect.sIndex*0.1) + 0.1 ;// create a different colour for each slice
        auto tileColor1  =  Colour::fromHSV (sliceColor,    // hue
                                              1.f,          // saturation
                                              1.f,          // brightness
                                              0.6f);        // alpha,
        
        Path path; // paint every slice as a path with a diffirent hue
        path.startNewSubPath (Point<float> (rect.xArrayPtr[(4*i)]   * screenSizeX * clickColour, rect.yArrayPtr[(4*i)]   * screenSizeY * clickColour));
        path.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+1] * screenSizeX * clickColour, rect.yArrayPtr[(4*i)+1] * screenSizeY * clickColour));
        path.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+2] * screenSizeX * clickColour, rect.yArrayPtr[(4*i)+2] * screenSizeY * clickColour));
        path.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+3] * screenSizeX * clickColour, rect.yArrayPtr[(4*i)+3] * screenSizeY * clickColour));
        path.closeSubPath();
        g.setColour(tileColor1);
        g.fillPath (path);
        
        Path stroke; // paint an black outline and a cross over the slices
        stroke.startNewSubPath (Point<float> (rect.xArrayPtr[(4*i)]   * screenSizeX * clickColour, rect.yArrayPtr[(4*i)]   * screenSizeY * clickColour));
        stroke.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+2] * screenSizeX * clickColour, rect.yArrayPtr[(4*i)+2] * screenSizeY * clickColour));
        stroke.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+1] * screenSizeX * clickColour , rect.yArrayPtr[(4*i)+1] * screenSizeY * clickColour));
        stroke.lineTo (Point<float>          (rect.xArrayPtr[(4*i)+3] * screenSizeX * clickColour, rect.yArrayPtr[(4*i)+3] * screenSizeY * clickColour));
        stroke.closeSubPath();
        g.setColour(Colour::fromHSV(1., 1., 0., 1.));
        g.strokePath(stroke, PathStrokeType(1.));
        g.strokePath(path, PathStrokeType(1.));
    
        g.setColour(Colour::fromHSV(1, 0, 0.2, 1)); // paint a black textbox in the center
        Rectangle<float> slice (path.getBounds().getCentreX()-30,path.getBounds().getCentreY()-20,60,40);
        g.fillRect(slice);

        g.setFont (20.0f); // paint the text overlay
        g.setColour (Colours::white);
        string text = "slice";
        g.drawText(text, path.getBounds(), Justification::centred);

    }

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
