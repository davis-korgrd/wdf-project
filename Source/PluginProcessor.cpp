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
    m_Hpf = new wdfOnePoleHPF::wdfOnePoleHighPass();
    m_Hpf->setResComponentVal(220e3);
    m_Hpf->setCapComponentVal(14.7e-9);
}

JuceTemplateAudioProcessor::~JuceTemplateAudioProcessor()
{
    delete m_Hpf;
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
    
    m_Hpf->setSamplerate(sampleRate);
    m_Hpf->reset();
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

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
//    double R = this->R;
//    double C = this->C;
//    float fs = getSampleRate();
    
    for (int j = 0; j < 1; ++j)
    {
        float* channelData = buffer.getWritePointer (j);
        float* channelDataR = buffer.getWritePointer (j + 1);
        
        m_Hpf->adaptTree();
        // ..do something to the data...
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            float out = 0;
            m_Hpf->processSample(channelData[i], out);
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
            m_Hpf->setResComponentVal(parameterValue);
            break;
        }
            
        default:
            break;
    }
}
