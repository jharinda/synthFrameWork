/*
  ==============================================================================

    Filter.cpp
    Created: 21 May 2021 11:14:08am
    Author:  Janith

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(SynthFrameWorkAudioProcessor& p) :audioProcessor(p)
{
    setSize(200, 200);
    filterMenu.addItem("LoPass",1);
    filterMenu.addItem("HiPass",2);
    filterMenu.addItem("BandPass",3);
    
    addAndMakeVisible(&filterMenu);
    filterMenu.addListener(this);

    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    cutoffSlider.setRange(audioProcessor.minCutoff, audioProcessor.maxCutoff);
    cutoffSlider.setValue(audioProcessor.defaultCutoff);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,audioProcessor.envValueWidth, audioProcessor.envValueHeight);
    addAndMakeVisible(&cutoffSlider);

    resSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    resSlider.setRange(audioProcessor.minResonance, audioProcessor.maxResonance);
    resSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, audioProcessor.envValueWidth, audioProcessor.envValueHeight);
    resSlider.setValue(audioProcessor.defaultResonance);
    addAndMakeVisible(&resSlider);

    filterTree = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree,audioProcessor.filterTypeId,filterMenu);
    cutoffTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,audioProcessor.cutoffId,cutoffSlider);
    resonanceTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,audioProcessor.resonanceId,resSlider);
}

Filter::~Filter()
{

}

void Filter::paint (juce::Graphics& g)
{
   
}

void Filter::resized()
{
    const int border = 40;
    
    juce::Rectangle<int> area = getLocalBounds().reduced(border);
    filterMenu.setBounds(area.removeFromTop(20));

    cutoffSlider.setBounds(0, 100, 100, 100);
    resSlider.setBounds(100, 100, 100, 100);

}

void Filter::comboBoxChanged(juce::ComboBox* box) 
{

}
