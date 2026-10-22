cmake_minimum_required(VERSION 3.22)
project(NoiseFix VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(JUCE GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 8.0.4)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(NoiseFix
    COMPANY_NAME "TotakanAudio"
    PLUGIN_MANUFACTURER_CODE Tota
    PLUGIN_CODE Nfix
    FORMATS VST3 Standalone
    PRODUCT_NAME "Noise-Fix"
    COPY_PLUGIN_AFTER_BUILD FALSE
)

target_sources(NoiseFix PRIVATE
    PluginProcessor.h
    PluginProcessor.cpp
    PluginEditor.h
)

target_link_libraries(NoiseFix PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)

juce_generate_juce_header(NoiseFix)
