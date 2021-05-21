/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
SynthFrameWorkAudioProcessor::SynthFrameWorkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),tree(*this,nullptr), attackTime(defaultAttackTime),
    decayTime(defaultDecayTime),
    sustainTime(defaultSustainTime),
    releaseTime(defaultReleaseTime)
#endif
{
    juce::NormalisableRange<float> attackParam(minAttackTime, maxAttackTime);
    juce::NormalisableRange<float> decayParam(minDecayTime, maxDecayTime);
    juce::NormalisableRange<float> sustainParam(minSustainTime, maxSustainTime);
    juce::NormalisableRange<float> releaseParam(minReleaseTime, maxReleaseTime);
    juce::NormalisableRange<float> waveTypeParam(minWaveType, maxWaveType);
    juce::NormalisableRange<float> filterTypeParam(minFilterType, maxFilterType);
    juce::NormalisableRange<float> cutoffParam(minCutoff, maxCutoff);
    juce::NormalisableRange<float> resonanceParam(minResonance, maxResonance);


    tree.createAndAddParameter(attackTimeId, attackTimeName, attackTimeName, attackParam, defaultAttackTime, nullptr, nullptr);
    tree.createAndAddParameter(decayTimeId, attackTimeName,decayTimeName, attackParam, defaultDecayTime, nullptr, nullptr);
    tree.createAndAddParameter(sustainTimeId, sustainTimeName, sustainTimeName, attackParam, defaultSustainTime, nullptr, nullptr);
    tree.createAndAddParameter(releaseTimeId, releaseTimeName, releaseTimeName, attackParam, defaultReleaseTime, nullptr, nullptr);

    tree.createAndAddParameter(waveTypeId, waveTypeName, waveTypeName, waveTypeParam, defaultWaveType, nullptr, nullptr);

    tree.createAndAddParameter(filterTypeId, filterTypeName, filterTypeName, filterTypeParam, defaultFilterType, nullptr, nullptr);
    tree.createAndAddParameter(cutoffId, cutoffName, cutoffName, cutoffParam, defaultCutoff, nullptr, nullptr);
    tree.createAndAddParameter(resonanceId, resonanceName, resonanceName, resonanceParam, defaultResonance, nullptr, nullptr);

    tree.state = juce::ValueTree("Foo");
    mySynth.clearVoices();

    for (int i = 0; i < 5; i++) {
        mySynth.addVoice(new SynthVoice());

    }

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

SynthFrameWorkAudioProcessor::~SynthFrameWorkAudioProcessor()
{
}

//==============================================================================
const juce::String SynthFrameWorkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthFrameWorkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameWorkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameWorkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthFrameWorkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthFrameWorkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthFrameWorkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthFrameWorkAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthFrameWorkAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthFrameWorkAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthFrameWorkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SynthFrameWorkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthFrameWorkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthFrameWorkAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        if (myVoice = dynamic_cast<SynthVoice*> (mySynth.getVoice(i)))
        {
            myVoice->setADSR(
                tree.getRawParameterValue(attackTimeId),
                tree.getRawParameterValue(decayTimeId),
                tree.getRawParameterValue(sustainTimeId),
                tree.getRawParameterValue(releaseTimeId)
            );

            myVoice->getWaveType(
                tree.getRawParameterValue(waveTypeId)
            );

            myVoice->setFilter(
                tree.getRawParameterValue(filterTypeId),
                tree.getRawParameterValue(cutoffId),
                tree.getRawParameterValue(resonanceId)
            );
        }
    }
    buffer.clear();
    mySynth.renderNextBlock(buffer,midiMessages,0,buffer.getNumSamples());

    
   


}

//==============================================================================
bool SynthFrameWorkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthFrameWorkAudioProcessor::createEditor()
{
    return new SynthFrameWorkAudioProcessorEditor (*this);
}

//==============================================================================
void SynthFrameWorkAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthFrameWorkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthFrameWorkAudioProcessor();
}
