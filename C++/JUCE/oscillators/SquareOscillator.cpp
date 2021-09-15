#include <cmath>
#include "SquareOscillator.h"

void Oscillators::SquareOscillator::updateAngleDelta(const double& frequency) {
	double cyclesPerSample = frequency / sampleRate;
	angleDelta = cyclesPerSample * 2.0;
}

Oscillators::SquareOscillator::SquareOscillator(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

void Oscillators::SquareOscillator::setSampleRate(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

float* Oscillators::SquareOscillator::getBlock(const float& frequency, const unsigned& blockSize) {
	updateAngleDelta(frequency);
	float* block = new float[blockSize];
	for (unsigned i = 0; i < blockSize; i++) {
		float angleMod = std::fmod(currentAngle, 2.0f) - 1.0f;
		block[i] = (angleMod < 0) ? -1.0f : 1.0f;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::SquareOscillator::getBlock(const float& frequency, const unsigned& blockSize, const float& amplitude) {
	updateAngleDelta(frequency);
	float* block = new float[blockSize];
	for (unsigned i = 0; i < blockSize; i++) {
		float angleMod = std::fmod(currentAngle, 2.0f) - 1.0f;
		block[i] = (angleMod < 0) ? -1.0f : 1.0f;
		block[i] *= amplitude;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::SquareOscillator::writeBlock(const float& frequency, const unsigned& blockSize, const float* block) {
	updateAngleDelta(frequency);
	for (unsigned i = 0; i < blockSize; i++) {
		float angleMod = std::fmod(currentAngle, 2.0f) - 1.0f;
		block[i] = (angleMod < 0) ? -1.0f : 1.0f;
		currentAngle += angleDelta;
	}
}

float* Oscillators::SquareOscillator::writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) {
	updateAngleDelta(frequency);
	for (unsigned i = 0; i < blockSize; i++) {
		float angleMod = std::fmod(currentAngle, 2.0f) - 1.0f;
		block[i] = (angleMod < 0) ? -1.0f : 1.0f;
		block[i] *= amplitude;
		currentAngle += angleDelta;
	}
}