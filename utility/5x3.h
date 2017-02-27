// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_5X3_CONSTANTS_H
#define STEPPER_CONTROLLER_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__AVR_ATmega2560__)

namespace stepper_controller
{
namespace constants
{
enum {DIGITAL_INPUT_COUNT=1};
enum {ENABLE_DISABLE_INPUT=0};

extern const size_t di_pins[DIGITAL_INPUT_COUNT];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const bool polarity_reversed_default[h_bridge_controller::constants::CHANNEL_COUNT];

extern const bool channels_enabled_default[h_bridge_controller::constants::CHANNEL_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
