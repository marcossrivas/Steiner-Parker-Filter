#include "VolumeMixer.h"


	VolumeMixer::VolumeMixer()
	{}
	VolumeMixer::~VolumeMixer()
	{}

	void VolumeMixer::processVolume(float* input, float* InAudio, float* OutAudio, float samplestoRender, double samplerate, float gain)
	{
		for (int i = 0; i < samplestoRender; i++) 
		
		{
			OutAudio[i] = gain*(input[i] + InAudio[i]);

		}
		

	}








