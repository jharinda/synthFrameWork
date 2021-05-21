/*
  ==============================================================================

    Oscillator.h
    Created: 21 May 2021 11:13:30am
    Author:  Janith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Oscillator  : public juce::Component
{
public:
    Oscillator();
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
