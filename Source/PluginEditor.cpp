/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameWorkAudioProcessorEditor::SynthFrameWorkAudioProcessorEditor (SynthFrameWorkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), envGUI (p), oscGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);

    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&oscGUI);
    
}

SynthFrameWorkAudioProcessorEditor::~SynthFrameWorkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameWorkAudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void SynthFrameWorkAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    const int componentWidth = 200;
    const int componentHeight = 200;

    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}
