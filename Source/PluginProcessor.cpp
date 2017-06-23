/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JuceTemplateAudioProcessor::JuceTemplateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    m_pHpf = new wdfSubmodule::wdfOnePoleHighPass();
    m_pHpf->setResComponentVal(220e3);
    m_pHpf->setCapComponentVal(14.7e-9);
    
    m_pGainProcessor = new wdfSubmodule::wdfGainProcessor;
    m_pGainProcessor->setResComponentVal(2.2e6);
    m_pGainProcessor->setCapComponentVal(22e-12);
    m_pGainProcessor->setLdrComponentVal(1);
    
    m_pEnvFollower = new wdfSubmodule::wdfEnvelopeFollower();
    m_pEnvFollower->setR1ComponentVal(110e3);
    m_pEnvFollower->setR2ComponentVal(1e3);
    m_pEnvFollower->setCapComponentVal(1e-6);
}

JuceTemplateAudioProcessor::~JuceTemplateAudioProcessor()
{
    delete m_pHpf;
}

//==============================================================================
const String JuceTemplateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceTemplateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceTemplateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double JuceTemplateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceTemplateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceTemplateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceTemplateAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceTemplateAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceTemplateAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceTemplateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    //const int totalNumInputChannels  = getTotalNumInputChannels();
    //const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    m_pHpf->setSamplerate(sampleRate);
    m_pHpf->reset();
    
    m_pGainProcessor->setSamplerate(sampleRate);
    m_pGainProcessor->reset();
    
    m_pEnvFollower->setSamplerate(sampleRate);
    m_pEnvFollower->reset();
    
    m_fFeedback = 1;
}

void JuceTemplateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceTemplateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JuceTemplateAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int j = 0; j < 1; ++j)
    {
        float* channelData = buffer.getWritePointer (j);
        float* channelDataR = buffer.getWritePointer (j + 1);
        
        m_pGainProcessor->setLdrComponentVal(m_fFeedback);
        
        m_pHpf->adaptTree();
        m_pGainProcessor->adaptTree();
        m_pEnvFollower->adaptTree();

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            float out = 0;
            m_pHpf->processSample(channelData[i], out);
//            m_pGainProcessor->processSample(out, out);
//            m_pEnvFollower->processSample(out, m_fFeedback);
            channelDataR[i] = out;
            channelData[i] = out;
        }
    }
}

//==============================================================================
bool JuceTemplateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceTemplateAudioProcessor::createEditor()
{
    return new JuceTemplateAudioProcessorEditor (*this);
}

//==============================================================================
void JuceTemplateAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceTemplateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceTemplateAudioProcessor();
}

void JuceTemplateAudioProcessor::setParameter(float parameterValue, int parameterIndex)
{
    switch (parameterIndex)
    {
        case 0:
        {
//            m_pHpf->setResComponentVal(parameterValue);
            break;
        }
            
        default:
            break;
    }
}
