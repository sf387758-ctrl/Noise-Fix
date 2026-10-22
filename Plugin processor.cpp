#include "PluginProcessor.h"
#include "PluginEditor.h"

NoiseFixAudioProcessor::NoiseFixAudioProcessor()
    : AudioProcessor (BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "Parameters", createParams())
{
}

NoiseFixAudioProcessor::~NoiseFixAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout NoiseFixAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back (std::make_unique<juce::AudioParameterFloat>(
        "harshFreq", "Harsh Freq", juce::NormalisableRange<float>(3000.0f, 8000.0f, 1.0f), 5200.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(
        "harshReduce", "Reduction", juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f), 65.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(
        "smooth", "Smoothness", juce::NormalisableRange<float>(0.1f, 1.0f, 0.01f), 0.7f));
    return { params.begin(), params.end() };
}

void NoiseFixAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) samplesPerBlock, (juce::uint32) getTotalNumOutputChannels() };
    deEsserChain.prepare (spec);
}

void NoiseFixAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    float freq = apvts.getRawParameterValue("harshFreq")->load();
    float reduction = apvts.getRawParameterValue("harshReduce")->load();
    float smooth = apvts.getRawParameterValue("smooth")->load();
    auto* filter1 = deEsserChain.get<0>().coefficients;
    *filter1 = *juce::dsp::IIR::Coefficients<float>::makeNotch (getSampleRate(), freq, 0.8f + smooth);
    auto* filter2 = deEsserChain.get<1>().coefficients;
    *filter2 = *juce::dsp::IIR::Coefficients<float>::makeLowShelf (getSampleRate(), 6500.0f, 0.7f, juce::Decibels::decibelsToGain(-reduction * 0.3f));
    deEsserChain.process (context);
}

juce::AudioProcessorEditor* NoiseFixAudioProcessor::createEditor() { return new juce::GenericAudioProcessorEditor (*this); }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new NoiseFixAudioProcessor(); }
