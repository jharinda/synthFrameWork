

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

    float attackTime;
    float decayTime;
    float sustainTime;
    float releaseTime;

    float minAttackTime = 0.1;
    float maxAttackTime = 5000;
    float defaultAttackTime = 4999;

    float minDecayTime = 1;
    float maxDecayTime = 2000;
    float defaultDecayTime = 200;

    float minSustainTime = 0;
    float maxSustainTime = 1;
    float defaultSustainTime = 1;

    float minReleaseTime = 0;
    float maxReleaseTime = 5000;
    float defaultReleaseTime = 100;

    string attackTimeId = "attack";
    string attackTimeName = "Attack";

    string decayTimeId = "decay";
    string decayTimeName = "Decay";

    string sustainTimeId = "sustain";
    string sustainTimeName = "Sustain";

    string releaseTimeId = "release";
    string releaseTimeName = "Release";

    juce::AudioProcessorValueTreeState tree;

private:
    //==============================================================================
    
    juce::Synthesiser mySynth;
    SynthVoice* myVoice;



    

    
    

    double lastSampleRate;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthFrameWorkAudioProcessor)
};
