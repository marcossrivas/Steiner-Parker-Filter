#include "SteinerParkerFilter.h"

SteinerParkerFilter::SteinerParkerFilter()
{}

SteinerParkerFilter::~SteinerParkerFilter()
{}

float SteinerParkerFilter::dvc1(float input, float vC1, float vC2, float reso, float cutoff)
{
	float dy = ((657967.6418439714 * vC1) + (reso * (input * (5540.78014184397 + (4432.624113475177 * reso)) +
	(526374.1134751772 * vC1) + (260416.6666666666 * vC2) + (208333.3333333333 * reso * vC2))) +
	(cutoff * (input * (-6925.975177304964 - (5540.78014184397 * reso)) + (664893.6170212765 * vC1) +
	(531914.8936170212 * reso * vC1) + (332446.80851063825 * vC2) + (reso * (797872.3404255317 +
	(425531.9148936169 * reso)) * vC2)))) / ((1.25 + reso) * (-2.4739583333333335 + (0.9791666666666666 * reso) +
	(cutoff * (-3.7239583333333335 + (-1.25 * cutoff) + reso))));

	return dy;
}

float SteinerParkerFilter::dvc2(float input, float vC1, float vC2, float reso, float cutoff)
{
	float dy = ((input * (-6925.975177304964 + (-5540.78014184397 * reso))) + ((-325520.83333333326 +
	(-332446.8085106382 * cutoff) + (-260416.6666666666 * reso) + (-265957.4468085106 * cutoff * reso)) * vC1) +
	((332446.80851063825 + (reso * (5540.78014184397 + (-265957.4468085106 * cutoff) + (-208333.3333333333 * reso) +
	(-212765.95744680846 * cutoff * reso)))) * vC2)) / ((1.25 + reso) * (-2.4739583333333335 + (0.9791666666666666 * reso) +
	(cutoff * (-3.7239583333333335 + (-1.25 * cutoff) + reso))));

	return dy;
}

void SteinerParkerFilter::processFilter(float* InAudio, float* OutAudio, float samplesToRender, double fs, float reso, float cutoff, float gain)
{
	// Heun method

	h = (1.0f / fs) / 2;

	for (int i = 0; i < samplesToRender; i++)
	{
		float input = InAudio[i];
		float k1 = dvc1(input, vC1, vC2, reso, cutoff);
		float k1_ = dvc2(input, vC1, vC2, reso, cutoff);

		float n1 = vC1 + (h * k1);
		float n2 = vC2 + (h * k1_);

		float k2 = dvc1(input, n1, n2, reso, cutoff);
		float k2_ = dvc2(input, n1, n2, reso, cutoff);

		vC1 = vC1 + (0.5 * h * (k1 + k2));
		vC2 = vC2 + (0.5 * h * (k1_ + k2_));

		OutAudio[i] = gain * ((((input * (0.020833333333333336 + (0.016666666666666666 * reso)) +
		(0.9791666666666666 + (cutoff)+(0.7833333333333333 * reso) + (0.8 * cutoff * reso))) * vC1) +
		((0.9791666666666666 + (0.7833333333333333 * reso) + (cutoff * (2.979166666666667 + cutoff +
		(2.3833333333333333 * reso) + (0.8 * cutoff * reso)))) * vC2)) / (1.9791666666666667 +
		(cutoff * (2.9791666666666665 + cutoff + (-0.8 * reso))) + (-0.7833333333333333 * reso)));
	}
}