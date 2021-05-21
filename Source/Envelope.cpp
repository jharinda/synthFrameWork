/*
  ==============================================================================

    Envelope.cpp
    Created: 21 May 2021 11:13:52am
    Author:  Janith

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"


//==============================================================================
Envelope::Envelope(SynthFrameWorkAudioProcessor& p):audioProcessor(p)
{
    setSize(200, 200);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(audioProcessor.minAttackTime, audioProcessor.maxAttackTime);
    attackSlider.setValue(audioProcessor.defaultAttackTime);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,30,30);

    addAndMakeVisible(&attackSlider);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(audioProcessor.minDecayTime, audioProcessor.maxDecayTime);
    decaySlider.setValue(audioProcessor.defaultDecayTime);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);

    addAndMakeVisible(&decaySlider);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(audioProcessor.minSustainTime, audioProcessor.maxSustainTime);
    sustainSlider.setValue(audioProcessor.defaultSustainTime);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);

    addAndMakeVisible(&sustainSlider);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(audioProcessor.minReleaseTime, audioProcessor.maxReleaseTime);
    releaseSlider.setValue(audioProcessor.defaultReleaseTime);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);
    addAndMakeVisible(&releaseSlider);

    attackTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, audioProcessor.attackTimeId, attackSlider);

    



}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    
}

void Envelope::resized()
{


}