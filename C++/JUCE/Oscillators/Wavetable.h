#ifndef LOTKEY_CPP_JUCE_WAVETABLE_H
#define LOTKEY_CPP_JUCE_WAVETABLE_H

#include <string>
#include <vector>
#include "Oscillators.h"

class Oscillators::Wavetable : public Oscillators::Oscillator {
private:
	double sampleRate = 48000;
	float currentIndex = 0, tableDelta = 0;
	std::vector<float> table;

	void updateAngleDelta(const double& frequency);
public:
	WavetableOscillator();
	WavetableOscillator(const std::vector<float>& waveTable);
	void setWavetable(const std::vector<float>& waveTable);
	void setSampleRate(const float& sampleRate);
	float* getBlock(const float& frequency, const unsigned& blockSize);
	float* getBlock(const float& frequency, const unsigned& blockSize, const float& amplitude);
	void writeBlock(const float& frequency, const unsigned& blockSize, const float* block) override;
	void writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) override;
};

#endif