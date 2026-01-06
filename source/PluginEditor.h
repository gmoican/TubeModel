#pragma once

#include "PluginProcessor.h"

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (TubeModelProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TubeModelProcessor& processorRef;
    
    // Custom Look and Feel
    punk_dsp::ExamplesLnF myCustomLnF;
    
    // Layout utilities
    juce::TextButton header, params;
    
    // Sliders - Rotary knobs
    juce::Slider driveSlider, outGainSlider, biasPreSlider, biasPostSlider, coeffPosSlider, coeffNegSlider, sagTimeSlider, harmGainSlider, harmBalanceSlider;
    juce::TextButton harmSCButton;
        
    // Attachments for linking sliders-parameters
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment, outGainAttachment, biasPreAttachment, biasPostAttachment, coeffPosAttachment, coeffNegAttachment, sagTimeAttachment, harmGainAttachment, harmBalanceAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> harmSCAttachment;
    
    void updateToggleButtonText()
    {
        // Check the current toggle state and update text accordingly
        if (harmSCButton.getToggleState())
            harmSCButton.setButtonText("Driven");
        else
            harmSCButton.setButtonText("Un-driven");
    }
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
