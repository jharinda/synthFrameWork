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

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySounds(juce::SynthesiserSound* sound)
    {

    }

    //================================================

    //starts when press a key
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {

    }

    //================================================

    //Starts when the key release
    void stopNote(float velocity, bool allowTailOff)
    {

    }

    //===============================================
    void pitchWheelMoved(int newPitchWheelValue)
    {

    }
    //===============================================

    void controllerMoved(int controllerNumber, int newControllerValue)
    {

    }

    //===============================================

    void renterNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {

    }

    //===============================================

private:

};