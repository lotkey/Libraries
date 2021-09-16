#include <cmath>
#include <vector>
#include "Wavetables.h"

std::vector<float> Oscillators::Wavetables::sawTable(const unsigned& size) {
	std::vector<float> table = std::vector<float>(size);

	double angleDelta = PI / (double)(size - 1);
	double currentAngle = 0.0;

	for (unsigned i = 0; i < size; i++) {
		table[i] = std::fmod(currentAngle, 2.0f) - 1.0f;
		currentAngle += angleDelta;
	}

	return table;
}

std::vector<float> Oscillators::Wavetables::sineTable(const unsigned& size) {
	std::vector<float> table = std::vector<float>(size);

	double angleDelta = PI / (double)(size - 1);
	double currentAngle = 0.0;

	for (unsigned i = 0; i < size; i++) {
		table[i] = std::sin(currentAngle);
		currentAngle += angleDelta;
	}

	return table;
}

std::vector<float> Oscillators::Wavetables::squareTable(const unsigned& size) {
	std::vector<float> table = std::vector<float>(size);

	double angleDelta = PI / (double)(size - 1);
	double currentAngle = 0.0;

	for (unsigned i = 0; i < size; i++) {
		float angleMod = std::fmod(currentAngle, 2.0f) - 1.0f;
		table[i] = (angleMod < 0) ? -1.0f : 1.0f;
		currentAngle += angleDelta;
	}

	return table;
}

std::vector<float> Oscillators::Wavetables::triangleTable(const unsigned& size) {
	std::vector<float> table = std::vector<float>(size);

	double angleDelta = PI / (double)(size - 1);
	double currentAngle = 0.0;

	for (unsigned i = 0; i < size; i++) {
		double mod = std::fmod(currentAngle, 2.0f) - 1.0f;
		double sample = (mod < 0.0f) ? mod + 0.5f : (1.0f - mod) - 0.5f;
		table[i] = sample * 2;
		currentAngle += angleDelta;
	}

	return table;
}

std::vector<float> Oscillators::Wavetables::getWavetable(const Oscillators::Type& type, const unsigned& size) {
	switch (type) {
	case(Oscillators::Type::SAW):
		return sawTable(size);
	case(Oscillators::Type::SINE):
		return sineTable(size);
	case(Oscillators::Type::SQUARE):
		return squareTable(size);
	case(Oscillators::Type::TRIANGLE):
		return triangleTable(size);
	default:
		return sineTable(size);
	}
}