#include "PluginEditor.h"
NoiseFixEditor::NoiseFixEditor(NoiseFixProcessor& p) : AudioProcessorEditor(&p), processor(p) {
    setSize(400, 300);
}
void NoiseFixEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawFittedText("Totakan Audio - Noise Fix", getLocalBounds(), juce::Justification::centred, 1);
}
void NoiseFixEditor::resized() {}
