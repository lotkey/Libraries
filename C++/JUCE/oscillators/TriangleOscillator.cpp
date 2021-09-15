#include <cmath>
#include "TriangleOscillator.h"

void Oscillators::TriangleOscillator::updateAngleDelta(const double& frequency) {
	double cyclesPerSample = frequency / sampleRate;
	angleDelta = cyclesPerSample * 2.0;
}

Oscillators::TriangleOscillator::TriangleOscillator(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

void Oscillators::TriangleOscillator::setSampleRate(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

float* Oscillators::TriangleOscillator::getBlock(const float& frequency, const unsigned& blockSize) {
	updateAngleDelta(frequency);
	float* block = new float[blockSize];
	for (unsigned i = 0; i < blockSize; i++) {
		float mod = std::fmod(currentAngle, 2.0f) - 1.0f;
		float sample = (mod < 0.0f) ? mod + 0.5f : (1.0f - mod) - 0.5f;
		block[i] = sample * 2;
		currentAngle += angleDelta;
	}
	return block;
}

float* Oscillators::TriangleOscillator::getBlock(const float& frequency, const unsigned& blockSize, const float& amplitude) {
	updateAngleDelta(frequency);
	float* block = new float[blockSize];
	for (unsigned i = 0; i < blockSize; i++) {
		float mod = std::fmod(currentAngle, 2.0f) - 1.0f;
		float sample = (mod < 0.0f) ? mod + 0.5f : (1.0f - mod) - 0.5f;
		block[i] = sample * 2 * amplitude;
		currentAngle += angleDelta;
	}
	return block;
}

void Oscillators::TriangleOscillator::writeBlock(const float& frequency, const unsigned& blockSize, const float* block) {
	updateAngleDelta(frequency);
	for (unsigned i = 0; i < blockSize; i++) {
		float mod = std::fmod(currentAngle, 2.0f) - 1.0f;
		float sample = (mod < 0.0f) ? mod + 0.5f : (1.0f - mod) - 0.5f;
		block[i] = sample * 2;
		currentAngle += angleDelta;
	}
}

void Oscillators::TriangleOscillator::writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) {
	updateAngleDelta(frequency);
	for (unsigned i = 0; i < blockSize; i++) {
		float mod = std::fmod(currentAngle, 2.0f) - 1.0f;
		float sample = (mod < 0.0f) ? mod + 0.5f : (1.0f - mod) - 0.5f;
		block[i] = sample * 2 * amplitude;
		currentAngle += angleDelta;
	}
}