

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"



//==============================================================================
/**
*/
class SynthFrameWorkAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SynthFrameWorkAudioProcessor();
    ~SynthFrameWorkAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void updateFilter();

    float attackTime;
    float decayTime;
    float sustainTime;
    float releaseTime;

    float minAttackTime = 0.0;
    float maxAttackTime = 5000;
    float defaultAttackTime = 0.5;

    float minDecayTime = 1;
    float maxDecayTime = 2000;
    float defaultDecayTime = 200;

    float minSustainTime = 0;
    float maxSustainTime = 1;
    float defaultSustainTime = 1;

    float minReleaseTime = 0;
    float maxReleaseTime = 5000;
    float defaultReleaseTime = 15;

    float envValueWidth = 40;
    float envValueHeight = 20;

    float minWaveType = 0;
    float maxWaveType = 3;
    float defaultWaveType = 0;

    float minFilterType = 0;
    float maxFilterType = 2;
    float defaultFilterType = 0;

    float minCutoff = 20;
    float maxCutoff = 20000;
    float defaultCutoff = 500;

    float minResonance = 1;
    float maxResonance = 10;
    float defaultResonance = 1;

    string attackTimeId = "attack";
    string attackTimeName = "Attack";

    string decayTimeId = "decay";
    string decayTimeName = "Decay";

    string sustainTimeId = "sustain";
    string sustainTimeName = "Sustain";

    string releaseTimeId = "release";
    string releaseTimeName = "Release";

    string waveTypeId = "waveType";
    string waveTypeName = "WaveType";

    string filterTypeId = "filterType";
    string filterTypeName = "filterType";

    string cutoffId = "cutoff";
    string cutoffName = "Cutoff";

    string resonanceId = "resonance";
    string resonanceName = "Resonance";
    

    juce::AudioProcessorValueTreeState tree;

private:
    //==============================================================================
    
    juce::Synthesiser mySynth;
    SynthVoice* myVoice;
    
    juce::dsp::ProcessorDuplicator <
        juce::dsp::StateVariableFilter::Filter<float>, 
        juce::dsp::StateVariableFilter::Parameters<float>
    > stateVariableFilter;


    double lastSampleRate;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthFrameWorkAudioProcessor)
};
