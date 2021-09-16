#include <fstream>
#include "Wavetable.h"

Oscillators::Wavetable::Wavetable() {
	table = Oscillators::Wavetables::getWavetable(Oscillators::Type::SINE, WAVETABLE_SIZE);
}

Oscillators::Wavetable::Wavetable(const Oscillators::Type& type) {
	table = Oscillators::Wavetables::getWavetable(type, WAVETABLE_SIZE);
}

void Oscillators::Wavetable::setWavetable(const Oscillators::Type& type) {
	table = Oscillators::Wavetables::getWavetable(type, WAVETABLE_SIZE);
}

void Oscillators::Wavetable::updateAngleDelta(const double& frequency) {
	auto tableSizeOverSampleRate = (float)table.size() / sampleRate;
	tableDelta = frequency * tableSizeOverSampleRate;
}

void Oscillators::Wavetable::setSampleRate(const float& sampleRate) {
	this->sampleRate = sampleRate;
}

float* Oscillators::Wavetable::getBlock(const float& frequency, const unsigned& blockSize) {
	updateDelta(frequency);
	float* block = new float[blockSize];
	
	if (table.size() == 0) {
		for (unsigned i = 0; i < blockSize; i++) {
			block[i] = 0;
		}
	}
	else {
		for (unsigned i = 0; i < blockSize; i++) {
			auto index0 = (unsigned int)currentIndex;
			auto index1 = (index0 + 1) % table.size();

			auto frac = currentIndex - (float)index0;
			auto value0 = table[index0];
			auto value1 = table[index1];

			auto currentSample = value0 + frac * (value1 - value0);

			if ((currentSample += tableDelta) > (float)table.size()) {
				currentIndex -= (float)table.size();
			}

			block[i] = currentSample;
		}
	}
	return block;
}

float* Oscillators::Wavetable::getBlock(const float& frequency, const unsigned& blockSize, const float& volume) {
	updateDelta(frequency);
	float* block = new float[blockSize];

	if (table.size() == 0) {
		for (unsigned i = 0; i < blockSize; i++) {
			block[i] = 0;
		}
	}
	else {
		for (unsigned i = 0; i < blockSize; i++) {
			auto index0 = (unsigned int)currentIndex;
			auto index1 = (index0 + 1) % table.size();

			auto frac = currentIndex - (float)index0;
			auto value0 = table[index0];
			auto value1 = table[index1];

			auto currentSample = value0 + frac * (value1 - value0);

			if ((currentSample += tableDelta) > (float)table.size()) {
				currentIndex -= (float)table.size();
			}

			block[i] = currentSample * volume;
		}
	}

	return block;
}

void Oscillators::Wavetable::writeBlock(const float& frequency, const unsigned& blockSize, const float* block) {
	updateDelta(frequency);

	if (table.size() == 0) {
		for (unsigned i = 0; i < blockSize; i++) {
			block[i] = 0;
		}
	}
	else {
		for (unsigned i = 0; i < blockSize; i++) {
			auto index0 = (unsigned int)currentIndex;
			auto index1 = (index0 + 1) % table.size();

			auto frac = currentIndex - (float)index0;
			auto value0 = table[index0];
			auto value1 = table[index1];

			auto currentSample = value0 + frac * (value1 - value0);

			if ((currentSample += tableDelta) > (float)table.size()) {
				currentIndex -= (float)table.size();
			}

			block[i] = currentSample;
		}
	}
}

void Oscillators::Wavetable::writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) {
	updateDelta(frequency);

	if (table.size() == 0) {
		for (unsigned i = 0; i < blockSize; i++) {
			block[i] = 0;
		}
	}
	else {
		for (unsigned i = 0; i < blockSize; i++) {
			auto index0 = (unsigned int)currentIndex;
			auto index1 = (index0 + 1) % table.size();

			auto frac = currentIndex - (float)index0;
			auto value0 = table[index0];
			auto value1 = table[index1];

			auto currentSample = value0 + frac * (value1 - value0);

			if ((currentSample += tableDelta) > (float)table.size()) {
				currentIndex -= (float)table.size();
			}

			block[i] = currentSample * amplitude;
		}
	}
}