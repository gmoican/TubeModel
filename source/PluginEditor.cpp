#include "PluginEditor.h"

PluginEditor::PluginEditor (TubeModelProcessor& p)
    : AudioProcessorEditor (&p),
      processorRef (p)
{
    juce::ignoreUnused (processorRef);
    juce::LookAndFeel::setDefaultLookAndFeel(&myCustomLnF);
    
    // --- LAYOUT ---
    header.setColour (juce::TextButton::buttonColourId, punk_dsp::UIConstants::background.brighter(0.5f)
                                                                               .withAlpha(0.25f)
                      );
    header.setEnabled(false);
    header.setColour(juce::TextButton::textColourOffId, punk_dsp::UIConstants::highlight);
    header.setColour(juce::TextButton::textColourOnId, punk_dsp::UIConstants::highlight);
    header.setButtonText ("Punk DSP - TubeModel");
    addAndMakeVisible (header);
    
    params.setColour (juce::TextButton::buttonColourId, punk_dsp::UIConstants::background.brighter(0.5f)
                                                                               .withAlpha(0.25f)
                      );
    params.setEnabled(false);
    addAndMakeVisible (params);
    
    // Drive
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    driveSlider.setRange(Parameters::driveMin, Parameters::driveMax, 0.1);
    driveSlider.setValue(Parameters::driveDefault);
    driveSlider.setName("Drive");
    addAndMakeVisible(driveSlider);
    
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::driveId, driveSlider);
    
    // Output Gain
    outGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    outGainSlider.setRange(Parameters::outGainMin, Parameters::outGainMax, 0.1);
    outGainSlider.setValue(Parameters::outGainDefault);
    outGainSlider.setName("Out");
    addAndMakeVisible(outGainSlider);
    
    outGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::outGainId, outGainSlider);
    
    // Bias (Pre-Drive)
    biasPreSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    biasPreSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    biasPreSlider.setRange(Parameters::biasMin, Parameters::biasMax, 0.01);
    biasPreSlider.setValue(Parameters::biasDefault);
    biasPreSlider.setName(u8"β\u2080");
    addAndMakeVisible(biasPreSlider);
    
    biasPreAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::preBiasId, biasPreSlider);

    // Bias (Post-Drive)
    biasPostSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    biasPostSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    biasPostSlider.setRange(Parameters::biasMin, Parameters::biasMax, 0.01);
    biasPostSlider.setValue(Parameters::biasDefault);
    biasPostSlider.setName(u8"β\u2081");
    addAndMakeVisible(biasPostSlider);
    
    biasPostAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::postBiasId, biasPostSlider);
    
    // Positive Denominator Coefficients
    coeffPosSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    coeffPosSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    coeffPosSlider.setRange(Parameters::coeffMin, Parameters::coeffMax, 0.01);
    coeffPosSlider.setValue(Parameters::coeffDefault);
    coeffPosSlider.setName(u8"+α");
    addAndMakeVisible(coeffPosSlider);
    
    coeffPosAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::coeffPosId, coeffPosSlider);
    
    // Negative Denominator Coefficients
    coeffNegSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    coeffNegSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    coeffNegSlider.setRange(Parameters::coeffMin, Parameters::coeffMax, 0.01);
    coeffNegSlider.setValue(Parameters::coeffDefault);
    coeffNegSlider.setName(u8"-α");
    addAndMakeVisible(coeffNegSlider);
    
    coeffNegAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::coeffNegId, coeffNegSlider);
    
    // Sag Time
    sagTimeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sagTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    sagTimeSlider.setRange(Parameters::sagTimeMin, Parameters::sagTimeMax, 0.1);
    sagTimeSlider.setValue(Parameters::sagTimeDefault);
    sagTimeSlider.setName("Sag");
    addAndMakeVisible(sagTimeSlider);
    
    sagTimeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::sagTimeId, sagTimeSlider);
    
    // Harmonic Gain (%)
    harmGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    harmGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    harmGainSlider.setRange(Parameters::harmonicsGainMin, Parameters::harmonicsGainMax, 0.1);
    harmGainSlider.setValue(Parameters::harmonicsGainDefault);
    harmGainSlider.setName("Xcite");
    addAndMakeVisible(harmGainSlider);
    
    harmGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::harmonicsGainId, harmGainSlider);
    
    // Harmonic Balance
    harmBalanceSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    harmBalanceSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    harmBalanceSlider.setRange(Parameters::harmonicsBalanceMin, Parameters::harmonicsBalanceMax, 0.1);
    harmBalanceSlider.setValue(Parameters::harmonicsBalanceDefault);
    harmBalanceSlider.setName("Bal");
    addAndMakeVisible(harmBalanceSlider);
    
    harmBalanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, Parameters::harmonicsBalanceId, harmBalanceSlider);
    
    // Harmonic Balance
    harmSCButton.setClickingTogglesState(true);
    harmSCButton.onClick = [this]() { updateToggleButtonText(); };
    updateToggleButtonText();
    addAndMakeVisible(harmSCButton);
    
    harmSCAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.apvts, Parameters::harmonicsSidechainId, harmSCButton);
    
    // Sizing calculations
    const int numCols = 5;
    const int numRows = 2;

    const int totalWidth = (numCols * (punk_dsp::UIConstants::knobSize + 2 * punk_dsp::UIConstants::margin)) + (10 * 2);
    const int totalHeight = punk_dsp::UIConstants::headerHeight + (numRows * (punk_dsp::UIConstants::knobSize + 2 * punk_dsp::UIConstants::margin)) + (10 * 2);
    
    setSize (totalWidth, totalHeight);
}

PluginEditor::~PluginEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (punk_dsp::UIConstants::background);
}

void PluginEditor::resized()
{
    // layout the positions of your child components here
    auto area = getLocalBounds();
    
    // --- LAYOUT SETUP ---
    auto headerArea = area.removeFromTop( punk_dsp::UIConstants::headerHeight );
    auto paramsArea = area.reduced( 10 );
    
    header.setBounds(headerArea);
    params.setBounds(paramsArea);
    
    // --- PARAMS LAYOUT ---
    juce::FlexBox fb;
    fb.flexDirection = juce::FlexBox::Direction::row;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    fb.alignContent = juce::FlexBox::AlignContent::spaceBetween;
    
    // Add sliders to the FlexBox
    fb.items.add(juce::FlexItem(driveSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                            .withMinHeight(punk_dsp::UIConstants::knobSize)
                                            .withMargin(punk_dsp::UIConstants::margin));
    fb.items.add(juce::FlexItem(outGainSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                              .withMinHeight(punk_dsp::UIConstants::knobSize)
                                              .withMargin(punk_dsp::UIConstants::margin));
    
    fb.items.add(juce::FlexItem(harmGainSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                               .withMinHeight(punk_dsp::UIConstants::knobSize)
                                               .withMargin(punk_dsp::UIConstants::margin));
    fb.items.add(juce::FlexItem(harmBalanceSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                                  .withMinHeight(punk_dsp::UIConstants::knobSize)
                                                  .withMargin(punk_dsp::UIConstants::margin));
    fb.items.add(juce::FlexItem(harmSCButton).withMinWidth(punk_dsp::UIConstants::knobSize)
                                             .withMinHeight(punk_dsp::UIConstants::knobSize)
                                             .withMargin(punk_dsp::UIConstants::margin));
    
    fb.items.add(juce::FlexItem(biasPreSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                              .withMinHeight(punk_dsp::UIConstants::knobSize)
                                              .withMargin(punk_dsp::UIConstants::margin));
    fb.items.add(juce::FlexItem(biasPostSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                               .withMinHeight(punk_dsp::UIConstants::knobSize)
                                               .withMargin(punk_dsp::UIConstants::margin));
    
    fb.items.add(juce::FlexItem(coeffPosSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                               .withMinHeight(punk_dsp::UIConstants::knobSize)
                                               .withMargin(punk_dsp::UIConstants::margin));
    fb.items.add(juce::FlexItem(coeffNegSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                               .withMinHeight(punk_dsp::UIConstants::knobSize)
                                               .withMargin(punk_dsp::UIConstants::margin));
    
    fb.items.add(juce::FlexItem(sagTimeSlider).withMinWidth(punk_dsp::UIConstants::knobSize)
                                              .withMinHeight(punk_dsp::UIConstants::knobSize)
                                              .withMargin(punk_dsp::UIConstants::margin));
    
    // Perform the layout
    fb.performLayout(paramsArea);
}
