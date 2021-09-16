#ifndef LOTKEY_CPP_OSCILLATOR_H
#define LOTKEY_CPP_OSCILLATOR_H

#include "Oscillators.h"
#include "JuceHeader.h"

#ifndef PI
#define PI juce::MathConstants<double>::pi
#endif

/// <summary>
/// Abstract base oscillator class
/// </summary>
class Oscillators::Oscillator {
private:
	float sampleRate;

	virtual void updateAngleDelta(const float& frequency) = 0;
public:
	/// <summary>
	/// Set the sample rate of the oscillator
	/// </summary>
	/// <param name="sampleRate"> - new sample rate </param>
	virtual void setSampleRate(const float& sampleRate) = 0;
	/// <summary>
	/// Get the next block from the oscillator
	/// </summary>
	/// <param name="frequency"> - pitch (Hz) of the entire block </param>
	/// <param name="blockSize"> - size of the block to return </param>
	/// <returns> block as a float* </returns>
	virtual float* getBlock(const float& frequency, const unsigned& blockSize) = 0;
	/// <summary>
	/// Get the next block from the oscillator
	/// </summary>
	/// <param name="frequency"> - pitch (Hz) of the entire block </param>
	/// <param name="blockSize"> - size of the block to return </param>
	/// <param name="amplitude"> - amplitude of the block to return </param>
	/// <returns> block as a float* </returns>
	virtual float* getBlock(const float& frequency, const unsigned& blockSize, const float& amplitude) = 0;
	/// <summary>
	/// Write the next block with the oscillator
	/// </summary>
	/// <param name="frequency"> - pitch (Hz) of the entire block </param>
	/// <param name="blockSize"> - size of the block to write </param>
	/// <param name="block"> - float* to write to </param>
	virtual void writeBlock(const float& frequency, const unsigned& blockSize, const float* block) = 0;
	/// <summary>
	/// Write the next block with the oscillator
	/// </summary>
	/// <param name="frequency"> - pitch (Hz) of the entire block </param>
	/// <param name="blockSize"> - size of the block to write </param>
	/// <param name="amplitude"> - amplitude of the block to write </param>
	/// <param name="block"> - float* to write to </param>
	virtual void writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) = 0;
};

#endif