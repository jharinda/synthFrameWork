/*
  ==============================================================================

    Filter.h
    Created: 21 May 2021 11:14:08am
    Author:  Janith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter();
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
