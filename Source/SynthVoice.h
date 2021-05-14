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
            std::cout << midiNoteNumber << std::endl;
            juce::Logger::outputDebugString(std::to_string(midiNoteNumber));
        


        }
        //============================================

        void stopNote (float velocity,bool allowTailOff)
        {
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

        }

private:
    double level;
    double frequencey;
};