cmake_minimum_required(VERSION 3.22)
project(Noise-Fix VERSION 1.0.0)

# JUCE ko add karo - ye line JUCE 8 ke liye zaroori hai
# Agar JUCE folder nahi hai to GitHub Actions khud download kar lega
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt)
    add_subdirectory(JUCE)
else()
    include(FetchContent)
    FetchContent_Declare(JUCE GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 8.0.4)
    FetchContent_MakeAvailable(JUCE)
endif()

juce_add_plugin(Noise-Fix
    COMPANY_NAME "TotakanAudio"
    PLUGIN_MANUFACTURER_CODE Tota
    PLUGIN_CODE Nfix
    FORMATS VST3 Standalone
    PRODUCT_NAME "Noise-Fix"
    COPY_PLUGIN_AFTER_BUILD TRUE
)

target_sources(Noise-Fix PRIVATE
    PluginProcessor.h
    PluginProcessor.cpp
    PluginEditor.h
)

target_link_libraries(Noise-Fix PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)

juce_generate_juce_header(Noise-Fix)
