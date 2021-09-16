#ifndef LOTKEY_CPP_TRIANGLEOSCILLATOR_H
#define LOTKEY_CPP_TRIANGLEOSCILLATOR_H

#include "Oscillators.h"

/// <summary>
/// Triangle Oscillator class
/// </summary>
class Oscillators::Triangle : public Oscillators::Oscillator {
private:
	float sampleRate = 48000;
	double angleDelta = 0.0f;
	double currentAngle = 0.0f;

	void updateAngleDelta(const double& frequency) override;
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Triangle() {}
	/// <summary>
	/// Constructor from sample rate
	/// </summary>
	/// <param name="sampleRate"> - sample rate (Hz) </param>
	Triangle(const float& sampleRate);
	/// <summary>
	/// Set the sample rate of the oscillator
	/// </summary>
	/// <param name="sampleRate"> - new sample rate </param>
	void setSampleRate(const float& sampleRate) override;
	/// <summary>
	/// Get the next block from the oscillator
	/// </summary>
	/// <param name="frequency"> - pitch (Hz) of the entire block </param>
	/// <param name="blockSize"> - size of the block to return </param>
	/// <returns> block as a float* </returns>
	float* getBlock(const float& frequency, const unsigned& blockSize) override;
	/// <summary>
	/// Get the next block from the oscillator
	/// </summary>
	/// <param name="frequency"> - pitch (Hz) of the entire block </param>
	/// <param name="blockSize"> - size of the block to return </param>
	/// <param name="amplitude"> - amplitude of the block to return </param>
	/// <returns> block as a float* </returns>
	float* getBlock(const float& frequency, const unsigned& blockSize, const float& amplitude) override;
	/// <summary>
	/// Write the next block with the oscillator
	/// </summary>
	/// <param name="frequency"> - pitch (Hz) of the entire block </param>
	/// <param name="blockSize"> - size of the block to write </param>
	/// <param name="block"> - float* to write to </param>
	virtual void writeBlock(const float& frequency, const unsigned& blockSize, const float* block) override;
	/// <summary>
	/// Write the next block with the oscillator
	/// </summary>
	/// <param name="frequency"> - pitch (Hz) of the entire block </param>
	/// <param name="blockSize"> - size of the block to write </param>
	/// <param name="amplitude"> - amplitude of the block to write </param>
	/// <param name="block"> - float* to write to </param>
	virtual void writeBlock(const float& frequency, const unsigned& blockSize, const float& amplitude, const float* block) override;
};

#endif