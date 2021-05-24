/*
  ==============================================================================

    SynthVoice.h
    Created: 1 Jan 2021 2:37:16pm
    Author:  Janith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

#include "maximilian.h"

class SynthVoice :public juce::SynthesiserVoice 
{
    public:
        bool canPlaySound(juce::SynthesiserSound* sound) 
        {
            return dynamic_cast<SynthSound*>(sound) != nullptr;
        }

        //===========================================

        void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchPosition) 
        {
            frequencey = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
            level = velocity;

            env1.trigger = 1;

        }
        //============================================

        void getWaveType(std::atomic<float>* selection)
        {
            theWave = *selection;
        }

        float setWaveType()
        {
            if (theWave == 0)
            {
                return osc1.sinewave(frequencey);
            }
            if (theWave == 1)
            {
                return osc1.saw(frequencey);
            }
            if (theWave == 2)
            {
                return osc1.triangle(frequencey);
            }
            if (theWave == 3)
            {
                return osc1.square(frequencey);
            }
            else
            {
                return osc1.sinewave(frequencey);
            }
        }

        void setADSR(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release )
        {
            env1.setAttack(double(*attack));
            
            env1.setDecay(double(*decay));
            env1.setSustain(double(*sustain));
            env1.setRelease(double(*release));

            
        }

        void setFilter(std::atomic<float>* filterTypeCombo, std::atomic<float>* cutoffCombo, std::atomic<float>* resonanceCombo)
        {
            filterType = *filterTypeCombo;
            cutoff = *cutoffCombo;
            resonance = *resonanceCombo;
        }

        float setEnv()
        {

            return env1.adsr(setWaveType(), env1.trigger)*level;
        }

       
        void stopNote (float velocity,bool allowTailOff)
        {
            env1.trigger = 0;
            allowTailOff = true;

            if (velocity == 0 )
                clearCurrentNote();
        }

        //============================================

        void pitchWheelMoved(int newPitchWheelValue) 
        {

        }

        //============================================

        void controllerMoved(int controllerNumber, int newControllerValue) 
        {

        }

        //============================================

        void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) 
        {

            for (int sample = 0; sample < numSamples; sample++)
            {

                for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
                {
                    outputBuffer.addSample(channel, startSample, setEnv());
                }
                ++startSample;
            }

        }

private:
    double level;
    double frequencey;
    double theWave;

    double filtered;
    double env;

    int filterType;
    float cutoff;
    float resonance;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;

};