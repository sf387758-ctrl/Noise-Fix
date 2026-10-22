#include "PluginProcessor.h"

class NoiseFixEditor : public juce::AudioProcessorEditor {
public:
    NoiseFixEditor(NoiseFixProcessor& p) : AudioProcessorEditor(&p) { setSize(400, 300); }
    void paint(juce::Graphics& g) override {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);
        g.setFont(20.0f);
        g.drawFittedText("Totakan Audio - Noise Fix\nHarshness Reducer 6.5kHz", getLocalBounds(), juce::Justification::centred, 2);
    }
    void resized() override {}
};

NoiseFixProcessor::NoiseFixProcessor() : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true)) {}
NoiseFixProcessor::~NoiseFixProcessor() {}

void NoiseFixProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::dsp::ProcessSpec spec{sampleRate, (juce::uint32)samplesPerBlock, (juce::uint32)getTotalNumOutputChannels()};
    lowPass.prepare(spec);
    *lowPass.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 6500.0f, 0.7f);
}
void NoiseFixProcessor::releaseResources() { lowPass.reset(); }
void NoiseFixProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);
    lowPass.process(ctx);
    for(int ch=0; ch<buffer.getNumChannels(); ++ch)
        for(int i=0; i<buffer.getNumSamples(); ++i){
            float x = buffer.getSample(ch,i);
            buffer.setSample(ch,i, std::tanh(x*1.2f)*0.83f);
        }
}
juce::AudioProcessorEditor* NoiseFixProcessor::createEditor() { return new NoiseFixEditor(*this); }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new NoiseFixProcessor(); }
