/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyResonatorAudioProcessor::MyResonatorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, "PARAMETERS", initializeGUI())
#endif
{
    initializeDSP();
}

MyResonatorAudioProcessor::~MyResonatorAudioProcessor()
{
}

void MyResonatorAudioProcessor::initializeDSP()
{
    for (int i = 0; i < getTotalNumOutputChannels(); i++)
    {
        ptrFilter[i] = std::unique_ptr<SteinerParkerFilter>(new SteinerParkerFilter());
        //ptrNoise[i] = std::unique_ptr<WhiteNoise>(new WhiteNoise());

    }

}


juce::AudioProcessorValueTreeState::ParameterLayout MyResonatorAudioProcessor::initializeGUI()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;


    params.push_back(std::make_unique<juce::AudioParameterFloat>("reso_ID", "resonance", 0.85f, 2.48f, 0.85f));//2.48 firme

    params.push_back(std::make_unique<juce::AudioParameterFloat>("gain_ID", "gain", 1.0f, 10.0f, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("cutoff_ID", "cutoff", 1.2f, 200.0f, 200.0f));



    return{ params.begin() , params.end() };


}


//==============================================================================
const juce::String MyResonatorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyResonatorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyResonatorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyResonatorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyResonatorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyResonatorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyResonatorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyResonatorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MyResonatorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyResonatorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MyResonatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
}

void MyResonatorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyResonatorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void MyResonatorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

       //ptrNoise[channel]->processSample(channelData, channelData, buffer.getNumSamples());

       ptrFilter[channel]->processFilter(channelData, channelData, buffer.getNumSamples(), getSampleRate(), *parameters.getRawParameterValue("reso_ID"), *parameters.getRawParameterValue("cutoff_ID"), *parameters.getRawParameterValue("gain_ID"));
    }
}

//==============================================================================
bool MyResonatorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MyResonatorAudioProcessor::createEditor()
{
    return new MyResonatorAudioProcessorEditor (*this);
}

//==============================================================================
void MyResonatorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MyResonatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyResonatorAudioProcessor();
}
