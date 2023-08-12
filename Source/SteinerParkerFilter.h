#pragma once
#include "JuceHeader.h"
#include "cmath"


class SteinerParkerFilter
{
	public:
		SteinerParkerFilter();

		~SteinerParkerFilter();

		float dvc1(float input, float vC1, float vC2, float reso, float cutoff);
		float dvc2(float input, float vC1, float vC2, float reso, float cutoff);

		void processFilter(float* InAudio, float* OutAudio, float samplestoRender, double fs, float reso, float cutoff, float gain);

	private:

		float h;

		//Circuit parmeters


		//aux variables for each filter
		float vC1{ 0.0f };
		float vC2{ 0.0f };

	};



