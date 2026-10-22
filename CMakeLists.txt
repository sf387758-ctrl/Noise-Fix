cmake_minimum_required(VERSION 3.22)
project(NoiseFix VERSION 1.0.0)
add_subdirectory(JUCE)
juce_add_plugin(NoiseFix
    COMPANY_NAME "TotakanAudio"
    IS_SYNTH FALSE NEEDS_MIDI_INPUT FALSE NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE Tota PLUGIN_CODE Nfix
    FORMATS VST3 Standalone
    PRODUCT_NAME "Noise-Fix"
)
target_sources(NoiseFix PRIVATE PluginProcessor.cpp)
target_compile_definitions(NoiseFix PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 JUCE_VST3_CAN_REPLACE_VST2=0)
target_link_libraries(NoiseFix PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
