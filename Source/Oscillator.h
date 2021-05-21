/*
  ==============================================================================

    Oscillator.h
    Created: 21 May 2021 11:13:30am
    Author:  Janith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Oscillator  : public juce::Component,
    public juce::ComboBox::Listener
{
public:
    Oscillator(SynthFrameWorkAudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:

    juce::ComboBox waveType;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscMenuTree;

    SynthFrameWorkAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)


};
