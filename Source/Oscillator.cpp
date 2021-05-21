/*
  ==============================================================================

    Oscillator.cpp
    Created: 21 May 2021 11:13:30am
    Author:  Janith

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFrameWorkAudioProcessor& p) :audioProcessor(p)
{
    setSize(200, 200);

    waveType.addItem("Sine", 1);
    waveType.addItem("Saw", 2);
    waveType.addItem("Triangle", 3);
    waveType.addItem("Squre", 4);

    addAndMakeVisible(&waveType);
    waveType.addListener(this);

    

    oscMenuTree = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, audioProcessor.waveTypeId, waveType);
    waveType.setJustificationType(juce::Justification::centred);



}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{

}

void Oscillator::resized()
{
    const int border = 40;

    juce::Rectangle<int> area = getLocalBounds().reduced(border);

    waveType.setBounds(area.removeFromTop(20));

}

void Oscillator::comboBoxChanged(juce::ComboBox* box)
{

}
