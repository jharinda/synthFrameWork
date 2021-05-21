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

            juce::Logger::outputDebugString(to_string(frequencey));

            env1.trigger = 1;
            
        


        }
        //============================================

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
            env1.setAttack(0.1);
            env1.setRelease(2000.0);
            env1.setDecay(500);
            env1.setSustain(0.8);

            for (int sample = 0; sample < numSamples; sample++)
            {
                double theWave = osc1.saw(frequencey);
                double  env = env1.adsr(theWave, env1.trigger) * level;
                double filtered = filter1.lores(env, 500, 0.4);

                for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
                {
                    outputBuffer.addSample(channel, startSample, filtered);
                }
                ++startSample;
            }

        }

private:
    double level;
    double frequencey;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;

};