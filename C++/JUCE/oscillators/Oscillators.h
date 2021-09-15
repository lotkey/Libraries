#ifndef LOTKEY_CPP_OSCILLATORS_H
#define LOTKEY_CPP_OSCILLATORS_H

/// <summary>
/// Namespace for all oscillator types
/// </summary>
namespace Oscillators {
	enum Type {
		SAW,
		SQUARE,
		SINE,
		TRIANGLE
	};

	class Oscillator;
	class SawOscillator;
	class SquareOscillator;
	class SineOscillator;
	class TriangleOscillator;
};

#include "Oscillator.h"
#include "SawOscillator.h"
#include "SquareOscillator.h"
#include "SineOscillator.h"
#include "TriangleOscillator.h"

#endif