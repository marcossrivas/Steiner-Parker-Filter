#pragma once
class Phaser
{

public:


	Phaser();
	~Phaser();

	float dvc1(float input, float vc1, float LFO);


	void processphaser(float* InAudio, float* OutAudio, float samplestoRender, double fs, float LFO, float gain);

private:

	float h;

	//Circuit parmeters


	//aux variables for each filter
	float vc1{ 0.0f };

};

