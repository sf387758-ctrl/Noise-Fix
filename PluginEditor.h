#pragma once
#include "PluginProcessor.h"
class NoiseFixEditor : public juce::AudioProcessorEditor {
public:
    NoiseFixEditor(NoiseFixProcessor&);
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    NoiseFixProcessor& processor;
};
