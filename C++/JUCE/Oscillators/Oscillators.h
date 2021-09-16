#ifndef LOTKEY_CPP_OSCILLATORS_H
#define LOTKEY_CPP_OSCILLATORS_H
#define WAVETABLE_SIZE 100

/// <summary>
/// Namespace for all oscillator types
/// </summary>
namespace Oscillators {

	namespace Wavetables;

	enum class Type {
		SAW,
		SQUARE,
		SINE,
		TRIANGLE,
		THEREMIN
	};

	class Oscillator;
	class Saw;
	class Square;
	class Sine;
	class Triangle;
	class Wavetable;
	
};

#include "Wavetables.h"
#include "Oscillator.h"
#include "Saw.h"
#include "Square.h"
#include "Sine.h"
#include "Triangle.h"
#include "Wavetable.h"

#endif