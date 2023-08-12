#include "WhiteNoise.h"


WhiteNoise::WhiteNoise()
{}

WhiteNoise::~WhiteNoise()
{}

void WhiteNoise::processSample(float* inAudio, float * outAudio, float samplesToRender)
{
	
	for (int i = 0; i < samplesToRender; i++)
	{
		float randomValue = randomGenerator.nextFloat() * 2.0f - 1.0f;

		outAudio[i] = randomValue;


	}
	







}