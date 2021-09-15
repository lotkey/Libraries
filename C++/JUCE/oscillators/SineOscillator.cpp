#include <cmath>
#include "SineOscillator.h"

void Oscillators::SineOscillator::updateAngleDelta(const double& frequency) {
    double cyclesPerSample = frequency / sampleRate;
    angleDelta = cyclesPerSample * 2.0 * PI;
}

Oscillators::SineOscillator::SineOscillator(const float& sampleRate) {
    this->sampleRate = sampleRate;
}

void Oscillators::SineOscillator::setSampleRate(const float& sampleRate) {
    this->sampleRate = sampleRate;
}

float* Oscillators::SineOscillator::getBlock(const float& frequency, const unsigned& blockSize) {
    updateAngleDelta(frequency);
    float* block = new float[blockSize];
    for (unsigned i = 0; i < blockSize; i++) {
        block[i] = (float)std::sin(currentAngle);
        currentAngle += angleDelta;
    }
    return block;
}

float* Oscillators::SineOscillator::getBlock(const float& frequency, const unsigned& blockSize, const float& amplitude) {
    updateAngleDelta(frequency);
    float* block = new float[blockSize];
    for (unsigned i = 0; i < blockSize; i++) {
        block[i] = (float)std::sin(currentAngle) * amplitude;
        currentAngle += angleDelta;
    }
    return block;
}

float* Oscillators::SineOscillator::writeBlock(const float& frequency, const unsigned& blockSize, const float* block) {
    updateAngleDelta(frequency);
    for (unsigned i = 0; i < blockSize; i++) {
        block[i] = (float)std::sin(currentAngle);
        currentAngle += angleDelta;
    }
    return block;
}

float* Oscillators::SineOscillator::writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) {
    updateAngleDelta(frequency);
    for (unsigned i = 0; i < blockSize; i++) {
        block[i] = (float)std::sin(currentAngle);
        block[i] *= amplitude;
        currentAngle += angleDelta;
    }
    return block;
}