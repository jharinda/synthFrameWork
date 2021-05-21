/*
  ==============================================================================

    Filter.h
    Created: 21 May 2021 11:14:08am
    Author:  Janith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component,
    public juce::ComboBox::Listener
{
public:
    Filter(SynthFrameWorkAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox* box) override;

private:

    SynthFrameWorkAudioProcessor& audioProcessor;

    juce::ComboBox filterMenu;
    juce::Slider cutoffSlider;
    juce::Slider resSlider;
   

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> cutoffTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> resonanceTree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
