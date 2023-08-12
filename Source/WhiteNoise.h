#pragma once
#include "JuceHeader.h"


class WhiteNoise
{
public:

	WhiteNoise();

	~WhiteNoise();

	void processSample(float* inAudio, float * outAudio, float samplesToRender);

private:

	juce::Random randomGenerator;
};

