/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CompressorSubmodules.h"

//==============================================================================
/**
*/
class JuceTemplateAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceTemplateAudioProcessor();
    ~JuceTemplateAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    
    void setParameter(float parameterValue, int parameterIndex);
    
    wdfSubmodule::wdfOnePoleHighPass * m_pHpf;
    wdfSubmodule::wdfGainProcessor * m_pGainProcessor;
    wdfSubmodule::wdfEnvelopeFollower * m_pEnvFollower;
    
    float m_fFeedback;
    float m_fLevel;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceTemplateAudioProcessor)
    
    //==============================================================================
    double *E, *U;
    double En;
    
    const double Is = 2.52e-9, Vt = 25.e-3;
};
