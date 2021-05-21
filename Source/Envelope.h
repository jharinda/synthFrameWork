/*
  ==============================================================================

    Envelope.h
    Created: 21 May 2021 11:13:52am
    Author:  Janith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Envelope  : public juce::Component
{
public:
    Envelope(SynthFrameWorkAudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    SynthFrameWorkAudioProcessor& audioProcessor;

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> attackTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> decayTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> releaseTree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
