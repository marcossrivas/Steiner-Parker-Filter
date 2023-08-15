#pragma once
class VolumeMixer
{

public:

	VolumeMixer();
	~VolumeMixer();

	void processVolume(float* input, float* InAudio, float* OutAudio, float samplestoRender, double samplerate, float gain);









};

