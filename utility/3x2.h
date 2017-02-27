// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_3X2_CONSTANTS_H
#define STEPPER_CONTROLLER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace stepper_controller
{
namespace constants
{
enum{TMC26X_COUNT=3};

extern const size_t cs_pins[TMC26X_COUNT];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long current_scale_default[TMC26X_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif