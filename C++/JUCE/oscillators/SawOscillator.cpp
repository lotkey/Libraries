#include <cmath>
#include "SawOscillator.h"

void Oscillators::SawOscillator::updateAngleDelta(const double& frequency) {
	double cyclesPerSample = frequency / sampleRate;
	angleDelta = cyclesPerSample * 2.0;
}

Oscillators::SawOscillator::SawOscillator(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

void Oscillators::SawOscillator::setSampleRate(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

float* Oscillators::SawOscillator::getBlock(const float& frequency, const unsigned& blockSize) {
	updateAngleDelta(frequency);
	float* block = new float[blockSize];
	for (unsigned i = 0; i < blockSize; i++) {
		block[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::SawOscillator::getBlock(const float& frequency, const unsigned& blockSize, const float& amplitude) {
	updateAngleDelta(frequency);
	float* block = new float[blockSize];
	for (unsigned i = 0; i < blockSize; i++) {
		block[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		block[i] *= amplitude;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::SawOscillator::writeBlock(const float& frequency, const unsigned& blockSize, const float* block) {
	updateAngleDelta(frequency);
	for (unsigned i = 0; i < blockSize; i++) {
		block[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::SawOscillator::writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) {
	updateAngleDelta(frequency);
	for (unsigned i = 0; i < blockSize; i++) {
		block[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		block[i] *= amplitude;
		currentAngle += angleDelta;
	}
	return block;
}