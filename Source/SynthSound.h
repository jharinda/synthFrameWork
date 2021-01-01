/*
  ==============================================================================

    SynthSound.h
    Created: 1 Jan 2021 2:37:04pm
    Author:  Janith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound :public juce::SynthesiserSound 
{
public:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        // returns true if this sound should be played when a midi note is pressed
        return true;
    }

    bool  appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};