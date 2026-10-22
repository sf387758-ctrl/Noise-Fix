#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
class NoiseFixAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    NoiseFixAudioProcessorEditor (NoiseFixAudioProcessor&);
    ~NoiseFixAudioProcessorEditor() override {}
    void paint (juce::Graphics&) override {}
    void resized() override {}
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseFixAudioProcessorEditor)
};
