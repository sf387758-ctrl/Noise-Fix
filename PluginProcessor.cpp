#include "PluginProcessor.h"
#include "PluginEditor.h"

NoiseFixProcessor::NoiseFixProcessor() : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true)) {}
NoiseFixProcessor::~NoiseFixProcessor() {}

void NoiseFixProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::dsp::ProcessSpec spec{sampleRate, (juce::uint32)samplesPerBlock, 2};
    lowPass.prepare(spec);
    lowPass.reset();
    *lowPass.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 6500.0f, 0.7f);
}
void NoiseFixProcessor::releaseResources() { lowPass.reset(); }

void NoiseFixProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);
    lowPass.process(ctx);
    // Soft harshness reduction
    for(int ch=0; ch<buffer.getNumChannels(); ++ch)
        for(int i=0; i<buffer.getNumSamples(); ++i)
            buffer.setSample(ch, i, std::tanh(buffer.getSample(ch, i) * 1.2f) * 0.83f);
}

juce::AudioProcessorEditor* NoiseFixProcessor::createEditor() { return new NoiseFixEditor(*this); }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new NoiseFixProcessor(); }
