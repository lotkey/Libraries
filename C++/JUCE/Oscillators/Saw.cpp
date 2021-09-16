#include <cmath>
#include "SawOscillator.h"

void Oscillators::Saw::updateAngleDelta(const double& frequency) {
	double cyclesPerSample = frequency / sampleRate;
	angleDelta = cyclesPerSample * 2.0;
}

Oscillators::Saw::Saw(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

void Oscillators::Saw::setSampleRate(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

float* Oscillators::Saw::getBlock(const float& frequency, const unsigned& blockSize) {
	updateAngleDelta(frequency);
	float* block = new float[blockSize];
	for (unsigned i = 0; i < blockSize; i++) {
		block[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::Saw::getBlock(const float& frequency, const unsigned& blockSize, const float& amplitude) {
	updateAngleDelta(frequency);
	float* block = new float[blockSize];
	for (unsigned i = 0; i < blockSize; i++) {
		block[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		block[i] *= amplitude;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::Saw::writeBlock(const float& frequency, const unsigned& blockSize, const float* block) {
	updateAngleDelta(frequency);
	for (unsigned i = 0; i < blockSize; i++) {
		block[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::Saw::writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) {
	updateAngleDelta(frequency);
	for (unsigned i = 0; i < blockSize; i++) {
		block[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		block[i] *= amplitude;
		currentAngle += angleDelta;
	}
	return block;
}