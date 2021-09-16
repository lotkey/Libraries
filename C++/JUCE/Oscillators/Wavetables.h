#ifndef LOTKEY_CPP_JUCE_WAVETABLES_H
#define LOTKEY_CPP_JUCE_WAVETABLES_H

#include <vector>
#include "Oscillators.h"

namespace Oscillators::Wavetables {
	std::vector<float> sawTable(const unsigned& size);
	std::vector<float> sineTable(const unsigned& size);
	std::vector<float> squareTable(const unsigned& size);
	std::vector<float> triangleTable(const unsigned& size);
	std::vector<float> getWavetable(const Oscillators::Type& type, const unsigned& size);
};

#endif