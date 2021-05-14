/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/
class SynthFrameWorkAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthFrameWorkAudioProcessorEditor (SynthFrameWorkAudioProcessor&);
    ~SynthFrameWorkAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Synthesiser mySynth;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthFrameWorkAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthFrameWorkAudioProcessorEditor)
};
