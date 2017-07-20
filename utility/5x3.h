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


#if defined(__MK64FX512__)

namespace stepper_controller
{
namespace constants
{
enum{DRIVER_COUNT=3};

extern const size_t cs_pins[DRIVER_COUNT];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
#endif
